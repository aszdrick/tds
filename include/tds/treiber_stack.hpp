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

#ifndef __TDS_TREIBER_STACK_HPP__
#define __TDS_TREIBER_STACK_HPP__

#include <atomic>
#include <memory>
#include <utility>

// Thread-safe Data Structures
namespace tds {
    template<typename VT>
    class treiber_stack {
     public:
        using value_type = VT;
        
        void push(const value_type&) noexcept;
        void push(value_type&&) noexcept;

        std::pair<value_type, bool> pop();
     private:
        struct node {
            value_type value;
            node* next;
        };

        std::atomic<node*> top;
    };

    template<typename VT>
    void treiber_stack<VT>::push(const value_type& value) noexcept {
        auto node = new treiber_stack<VT>::node{value, top};
        top = node;
    }

    template<typename VT>
    void treiber_stack<VT>::push(value_type&& value) noexcept {
        auto new_top = new treiber_stack<VT>::node{std::move(value), nullptr};
        auto old_top = top.load(std::memory_order_acquire);
        new_top->next = old_top;

        while (!top.compare_exchange_weak(old_top, new_top, std::memory_order_release, std::memory_order_acquire)) {
            old_top = top.load(std::memory_order_acquire);
            new_top->next = old_top;
        }
    }

    template<typename VT>
    std::pair<VT, bool> treiber_stack<VT>::pop() {
        auto old_top = top.load(std::memory_order_acquire);
        if (old_top) {
            auto new_top = old_top->next;
            auto data = old_top->value;
            while (!top.compare_exchange_weak(old_top, new_top, std::memory_order_release, std::memory_order_acquire)) {
                old_top = top.load(std::memory_order_acquire);
                if (!old_top) {
                    return {value_type(), false};
                }
                new_top = old_top->next;
                data = old_top->value;
            }
            return {data, true};
        }

        return {value_type(), false};
    }
}

#endif /* __TDS_TREIBER_STACK_HPP__ */
