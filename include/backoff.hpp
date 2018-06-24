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

#ifndef __BS_BACKOFF_HPP__
#define __BS_BACKOFF_HPP__

#include <chrono>

// Back-Off Strategies 
namespace bs {
    class no_backoff {
     public:
        void operator()() { }
    };

    class exponential {
     public:
        exponential(unsigned = 1, unsigned = 2, unsigned = 1000);

        void operator()();
     private:
        unsigned const step;
        unsigned const max;
        std::chrono::nanoseconds delay;
    };

    exponential::exponential(unsigned init, unsigned step, unsigned max) :
     step{step},
     max{max},
     delay{init} { }

    void exponential::operator()() {
        auto end = std::chrono::steady_clock::now() + delay;
        while (std::chrono::steady_clock::now() < end);
        delay *= 2;
    }
}

#endif /* __BS_BACKOFF_HPP__ */
