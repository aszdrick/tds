///////////////////////////////////////////////////////////////////////////////
////////////////////////// <github.com/aszdrick/tds> //////////////////////////
//////////////////////////// <aszdrick@gmail.com> /////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2017-2018 Marleson Graf

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


template<template<class> class DS>
dsb::prodcon<DS>::prodcon(unsigned np, unsigned nc, unsigned pd, unsigned cd) :
 nproducers{np},
 nconsumers{nc},
 produce_delay{pd},
 consume_delay{cd},
 active{np} { }

template<template<class> class DS>
void dsb::prodcon<DS>::run(unsigned n, unsigned seed) {
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < nproducers; ++i) {
        threads.emplace_back(&prodcon<DS>::produce, this, n, seed);
    }

    for (unsigned i = 0; i < nconsumers-1; ++i) {
        threads.emplace_back(&prodcon<DS>::consume, this);
    }

    consume();

    for (auto& thread : threads) {
        thread.join();
    }

    active.store(nproducers, std::memory_order_relaxed);
}

template<template<class> class DS>
void dsb::prodcon<DS>::produce(unsigned n_iterations, unsigned seed) {
    std::mt19937_64 gen(seed);
    
    for (unsigned i = 0; i < n_iterations; ++i) {
        unsigned number = gen() % std::numeric_limits<unsigned>::max();
        data.push(number);
        auto start = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - start < produce_delay);
    }
    active.fetch_sub(1);
}

template<template<class> class DS>
void dsb::prodcon<DS>::consume() {
    bool valid = true;

    while (valid || active.load(std::memory_order_relaxed) || data.size()) {
        valid = data.pop().second;
        if (valid) {
            auto start = std::chrono::steady_clock::now();
            while (std::chrono::steady_clock::now() - start < consume_delay);
        }
    }
}
