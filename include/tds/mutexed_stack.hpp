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

#include <stack>

#include <iostream>

// Thread-safe Data Structures
namespace tds {
    // Non-intrusive mutexed stack
    template<typename VT>
    class mutexed_stack {
        struct node {
            VT value;
            node* next;
        };
     public:
        using value_type = VT;

        ~mutexed_stack() {
            std::cout << "size = " << inner_stack.size() << std::endl;
        }

        void push(const value_type&);
        void push(value_type&&);

        std::pair<value_type, bool> pop();

        auto size() { return inner_stack.size(); }
     private:
        std::mutex mutex;
        std::stack<VT> inner_stack;
        // node* top;
    };

    template<typename VT>
    void mutexed_stack<VT>::push(const value_type& value) {
        std::lock_guard<std::mutex> guard(mutex);
        // top = new node{value, top};
        inner_stack.push(value);
    }

    template<typename VT>
    void mutexed_stack<VT>::push(value_type&& value) {
        std::lock_guard<std::mutex> guard(mutex);
        // top = new node{std::move(value), top};
        inner_stack.push(std::move(value));
    }

    template<typename VT>
    std::pair<VT, bool> mutexed_stack<VT>::pop() {
        std::lock_guard<std::mutex> guard(mutex);
        // if (top) {
        //     auto temp = top->value;
        //     auto new_top = top->next;
        //     delete top;
        //     top = new_top;
        if (!inner_stack.empty()) {
            auto temp = inner_stack.top();
            inner_stack.pop();
            return {temp, true};
        }
        return {0, false};
    }
}

#endif /* __LBDS_MUTEXED_STACK_HPP__ */
