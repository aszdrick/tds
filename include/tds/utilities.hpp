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

#ifndef __TDS_UTILITIES_HPP__
#define __TDS_UTILITIES_HPP__

namespace tds {
    class thread_barrier {
     public:
        explicit thread_barrier(size_t count) : counter{count} { }

        void wait() {
            std::unique_lock<std::mutex> lock{mutex};
            if (--counter == 0) {
                cv.notify_all();
            } else {
                cv.wait(lock, [this] { return counter == 0; });
            }
        }
     private:
        std::mutex mutex;
        std::condition_variable cv;
        std::size_t counter;
    };
}

#endif /* __TDS_UTILITIES_HPP__ */
