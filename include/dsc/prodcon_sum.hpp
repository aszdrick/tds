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

#ifndef __DSC_PRODCON_SUM_HPP__
#define __DSC_PRODCON_SUM_HPP__

#include <cstdint>
#include <future>
#include <mutex>
#include <random>

// Data Structure Checkers
namespace dsc {
    // Producer-Consumer sum verification
    template<template<class> class CDS>
    class prodcon_sum {
     public:
        template<typename... CDSArgs>
        prodcon_sum(unsigned, unsigned, unsigned = 100, CDSArgs&&...);
        bool run(unsigned, unsigned);
     private:
        unsigned nproducers;
        unsigned nconsumers;
        unsigned gen_limit;
        unsigned active_producers = 0;
        std::mutex producers_mutex;
        CDS<intmax_t> data_structure;

        void active(int = 1);
        intmax_t consume();
        intmax_t produce(unsigned, unsigned);
    };

    template<template<class> class CDS>
    template<typename... CDSArgs>
    prodcon_sum<CDS>::prodcon_sum(unsigned np, unsigned nc, unsigned limit,
                                  CDSArgs&&... args):
      nproducers(np),
      nconsumers(nc),
      gen_limit(limit),
      data_structure{std::forward<CDSArgs>(args)...} {

    }

    template<template<class> class CDS>
    bool prodcon_sum<CDS>::run(unsigned n_iterations, unsigned seed) {
        std::vector<std::future<intmax_t>> producer_futures(nproducers);
        std::vector<std::future<intmax_t>> consumer_futures(nconsumers);
        intmax_t consumer_total_sum = 0;
        intmax_t producer_total_sum = 0;

        for (unsigned i = 0; i < std::max(nconsumers, nproducers); ++i) {
            if (i < nproducers) {
                producer_futures[i] = std::async(
                    [this](unsigned n_iterations, unsigned seed) {
                        return this->produce(n_iterations, seed);
                    }, n_iterations, seed
                );
            }
            if (i < nconsumers) {
                consumer_futures[i] = std::async([this]() {
                    return this->consume();
                });
            }
        }

        for (auto& future : consumer_futures) {
            consumer_total_sum += future.get();
        }

        for (auto& future : producer_futures) {
            producer_total_sum += future.get();
        }

        return consumer_total_sum == producer_total_sum;
    }

    template<template<class> class CDS>
    void prodcon_sum<CDS>::active(int value) {
        std::lock_guard<std::mutex> guard(producers_mutex);
        active_producers += value;
    }

    template<template<class> class CDS>
    intmax_t prodcon_sum<CDS>::consume() {
        intmax_t partial_sum = 0;
        intmax_t number = 0;
        bool valid = true;
        while (valid || active_producers > 0) {
            std::tie(number, valid) = data_structure.pop();
            if (valid) {
                partial_sum += number;
            }
        }
        return partial_sum;
    }

    template<template<class> class CDS>
    intmax_t prodcon_sum<CDS>::produce(unsigned n_iterations, unsigned seed) {
        active();
        std::mt19937_64 gen(seed);
        intmax_t partial_sum = 0;

        for (intmax_t i = 0; i < n_iterations; ++i) {
            unsigned number = gen() % gen_limit;
            data_structure.push(number);
            partial_sum += number;
        }

        active(-1);
        return partial_sum;
    }
}

#endif /* __DSC_PRODCON_SUM_HPP__ */
