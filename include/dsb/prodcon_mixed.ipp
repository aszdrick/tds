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

#include <cassert>

template<template<class...> class D>
dsb::prodcon_mixed<D>::prodcon_mixed(unsigned nw, unsigned pd, unsigned cd):
 nworkers{nw},
 produce_delay{pd},
 consume_delay{cd} { }

template<template<class...> class D>
void dsb::prodcon_mixed<D>::run(unsigned n, unsigned seed) {
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < nworkers-1; ++i) {
        threads.emplace_back(&prodcon_mixed<D>::work, this, n, seed);
    }

    work(n, seed);

    for (auto& thread : threads) {
        thread.join();
    }
}

template<template<class...> class D>
void dsb::prodcon_mixed<D>::work(unsigned n, unsigned seed) {
    std::mt19937_64 gen(seed);

    for (unsigned i = 0; i < n; ++i) {
        unsigned number = gen() % std::numeric_limits<unsigned>::max();

        auto end = std::chrono::steady_clock::now() + produce_delay;
        while (std::chrono::steady_clock::now() < end);

        data.push(number);

        end = std::chrono::steady_clock::now() + consume_delay;
        while (std::chrono::steady_clock::now() < end);

        data.pop();
    }
}
