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

#ifndef __DSB_PRODCON_MIXED_HPP__
#define __DSB_PRODCON_MIXED_HPP__

#include <atomic>
#include <chrono>
#include <cstdint>
#include <limits>
#include <future>
#include <random>
#include <unordered_map>

// Data Structure Benchmarks
namespace dsb {
    // Producer-Consumer precise verification
    template<template<class...> class DS>
    class prodcon_mixed {
     public:
        prodcon_mixed(unsigned, unsigned, unsigned);

        void run(unsigned, unsigned);
     private:
        unsigned nworkers;
        std::chrono::nanoseconds produce_delay;
        std::chrono::nanoseconds consume_delay;
        DS<unsigned> data;

        void work(unsigned, unsigned);
    };
}

#include "prodcon_mixed.ipp"

#endif /* __DSB_PRODCON_MIXED_HPP__ */
