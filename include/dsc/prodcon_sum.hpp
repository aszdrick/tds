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

#include <atomic>
#include <cstdint>
#include <future>
#include <random>

// Data Structure Checkers
namespace dsc {
    // Producer-Consumer sum verification
    template<template<class...> class DS>
    class prodcon_sum {
     public:
        prodcon_sum(unsigned, unsigned, unsigned = 100);
        bool run(unsigned, unsigned);
     private:
        unsigned nproducers;
        unsigned nconsumers;
        unsigned gen_limit;
        std::atomic_uint active;
        DS<intmax_t> data;

        intmax_t consume();
        intmax_t produce(unsigned, unsigned);
    };
}

#include "prodcon_sum.ipp"

#endif /* __DSC_PRODCON_SUM_HPP__ */
