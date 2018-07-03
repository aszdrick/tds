///////////////////////////////////////////////////////////////////////////////
////////////////////////// <github.com/aszdrick/tds> //////////////////////////
//////////////////////////// <aszdrick@gmail.com> /////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018 Marleson Graf

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

template<template<class...> class DS>
dsc::prodcon_sum<DS>::prodcon_sum(unsigned np, unsigned nc, unsigned limit) :
  nproducers{np},
  nconsumers{nc},
  gen_limit{limit},
  active{np} {
}

template<template<class...> class DS>
bool dsc::prodcon_sum<DS>::run(unsigned n_iterations, unsigned seed) {
    std::vector<std::future<intmax_t>> producer_futures(nproducers);
    std::vector<std::future<intmax_t>> consumer_futures(nconsumers);
    intmax_t consumer_total_sum = 0;
    intmax_t producer_total_sum = 0;

    for (unsigned i = 0; i < std::max(nconsumers, nproducers); ++i) {
        if (i < nproducers) {
            producer_futures[i] = std::async(std::launch::async,
                &prodcon_sum<DS>::produce, this, n_iterations, seed);
        }
        if (i < nconsumers) {
            consumer_futures[i] = std::async(std::launch::async,
                &prodcon_sum<DS>::consume, this);
        }
    }

    for (auto& future : consumer_futures) {
        consumer_total_sum += future.get();
    }

    for (auto& future : producer_futures) {
        producer_total_sum += future.get();
    }

    active.store(nproducers, std::memory_order_relaxed);
    return consumer_total_sum == producer_total_sum;
}

template<template<class...> class DS> intmax_t dsc::prodcon_sum<DS>::consume() {
    intmax_t partial_sum = 0;
    intmax_t number = 0;
    bool valid = true;

    while (valid || active.load(std::memory_order_relaxed) || data.size()) {
        std::tie(number, valid) = data.pop();
        if (valid) {
            partial_sum += number;
        }
    }
    return partial_sum;
}

template<template<class...> class DS>
intmax_t dsc::prodcon_sum<DS>::produce(unsigned n_iterations, unsigned seed) {
    std::mt19937_64 gen(seed);
    intmax_t partial_sum = 0;

    for (intmax_t i = 0; i < n_iterations; ++i) {
        unsigned number = gen() % gen_limit;
        partial_sum += number;
        data.push(number);
    }

    active.fetch_sub(1);
    return partial_sum;
}
