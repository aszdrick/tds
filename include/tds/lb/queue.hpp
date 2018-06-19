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

#ifndef __TDS_LB_QUEUE_HPP__
#define __TDS_LB_QUEUE_HPP__

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

// Thread-safe Data Structures - Lock-Based
namespace tds { namespace lb {
    // Queue with global mutex
    template<typename VT>
    class queue {
     public:
        using value_type = VT;

        void push(value_type);
        std::pair<value_type, bool> pop();
        size_t size() const;
     private:
        std::mutex mutex;
        std::queue<VT> inner_queue;
    };

    // Queue with one mutex to push and another to pop
    template<typename VT>
    class dual_lock_queue {
        struct node {
            VT value;
            node* next;
        };
     public:
        using value_type = VT;

        dual_lock_queue();
        ~dual_lock_queue();

        void push(value_type);
        std::pair<value_type, bool> pop();
        size_t size() const;
     private:
        std::mutex push_mutex;
        std::mutex pop_mutex;
        std::atomic_size_t size_counter{0};
        node* head;
        node *tail;
    };
}}

#include "queue.ipp"

#endif /* __TDS_LB_QUEUE_HPP__ */
