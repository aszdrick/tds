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

#ifndef __LBDS_MUTEXED_STACK_HPP__
#define __LBDS_MUTEXED_STACK_HPP__

#include <memory>
#include <mutex>
#include <utility>

// Thread-safe Data Structures
namespace tds {
    // Non-intrusive mutexed stack
    template<typename VT>
    class mutexed_stack {
     public:
        using value_type = VT;

        void push(const value_type&);
        void push(value_type&&);

        std::pair<value_type, bool> pop();
     private:
        struct node {
            value_type value;
            node* next;
        };

        node* top = nullptr;
        std::mutex mutex;
    };

    template<typename VT>
    void mutexed_stack<VT>::push(const value_type& value) {
        std::lock_guard<std::mutex> guard(mutex);
        auto node = new mutexed_stack<VT>::node{value, top};
        top = node;
    }

    template<typename VT>
    void mutexed_stack<VT>::push(value_type&& value) {
        std::lock_guard<std::mutex> guard(mutex);
        auto node = new mutexed_stack<VT>::node{std::move(value), top};
        top = node;
    }

    template<typename VT>
    std::pair<VT, bool> mutexed_stack<VT>::pop() {
        std::lock_guard<std::mutex> guard(mutex);
        if (top) {
            VT data = top->value;
            auto next = top->next;
            delete top;
            top = next;
            return {data, true};
        } else {
            return {0, false};
        }
    }
}

#endif /* __LBDS_MUTEXED_STACK_HPP__ */
