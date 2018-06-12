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

#ifndef __DSC_PRODCON_PRECISE_HPP__
#define __DSC_PRODCON_PRECISE_HPP__

#include <atomic>
#include <cstdint>
#include <future>
#include <mutex>
#include <random>
#include <unordered_map>

// Data Structure Checkers
namespace dsc {
    // Producer-Consumer precise verification
    template<template<class> class CDS>
    class prodcon_precise {
        using CType = std::unordered_map<unsigned, uintmax_t>;
     public:
        ~prodcon_precise() = default;

        template<typename... CDSArgs>
        prodcon_precise(unsigned, unsigned, unsigned = 100, CDSArgs&&...);
        bool run(unsigned, unsigned);
     private:
        unsigned nproducers;
        unsigned nconsumers;
        unsigned gen_limit;
        std::atomic_uint active_producers;
        CDS<unsigned> data_structure;

        CType consume();
        CType produce(unsigned, unsigned);
    };

    template<template<class> class CDS>
    template<typename... CDSArgs>
    prodcon_precise<CDS>::prodcon_precise(unsigned np, unsigned nc, unsigned limit,
                                  CDSArgs&&... args):
      nproducers{np},
      nconsumers{nc},
      gen_limit{limit},
      active_producers{0},
      data_structure{std::forward<CDSArgs>(args)...} {
    }

    template<template<class> class CDS>
    bool prodcon_precise<CDS>::run(unsigned n_iterations, unsigned seed) {
        std::vector<std::future<CType>> producer_futures(nproducers);
        std::vector<std::future<CType>> consumer_futures(nconsumers);
        CType producer_counters;
        CType consumer_counters;

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

        for (unsigned i = 0; i < producer_futures.size(); ++i) {
            auto counters = producer_futures[i].get();
            for (auto counter : counters) {
                if (!producer_counters.count(counter.first)) {
                    producer_counters[counter.first] = counter.second;
                } else {
                    producer_counters[counter.first] += counter.second;
                }
            }
        }

        for (unsigned i = 0; i < consumer_futures.size(); ++i) {
            auto counters = consumer_futures[i].get();
            for (auto counter : counters) {
                if (!consumer_counters.count(counter.first)) {
                    consumer_counters[counter.first] = counter.second;
                } else {
                    consumer_counters[counter.first] += counter.second;
                }
            }
        }
        return producer_counters == consumer_counters;
    }

    template<template<class> class CDS>
    typename prodcon_precise<CDS>::CType prodcon_precise<CDS>::consume() {
        CType counters;
        unsigned number = 0;
        bool valid = true;
        while(active_producers.load() == 0); // valgrind doesn't like that
        while (valid || active_producers.load() > 0) {
            std::tie(number, valid) = data_structure.pop();
            if (valid) {
                if (!counters.count(number)) {
                    counters[number] = 1;
                } else {
                    counters[number] += 1;
                }
            }
        }
        return counters;
    }

    template<template<class> class CDS>
    typename prodcon_precise<CDS>::CType prodcon_precise<CDS>::produce(
                                        unsigned n_iterations, unsigned seed) {
        active_producers.fetch_add(1);
        std::mt19937_64 gen(seed);
        CType counters;

        for (unsigned i = 0; i < n_iterations; ++i) {
            unsigned number = gen() % gen_limit;
            data_structure.push(number);
            if (!counters.count(number)) {
                counters[number] = 1;
            } else {
                counters[number] += 1;
            }
        }

        active_producers.fetch_sub(1);
        return counters;
    }
}

#endif /* __DSC_PRODCON_PRECISE_HPP__ */
