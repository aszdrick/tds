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


template<typename VT>
tds::treiber_stack<VT>::~treiber_stack() {
    auto curr = top.load();
    while(curr) {
        auto temp = curr->next;
        delete curr;
        curr = temp;
    }
}

template<typename VT>
void tds::treiber_stack<VT>::push(const value_type& value) {
    auto newtop = new tds::treiber_stack<VT>::node{value};
    newtop->next = top;

    while (!top.compare_exchange_weak(newtop->next, newtop));
    size_counter.fetch_add(1);
}

template<typename VT>
void tds::treiber_stack<VT>::push(value_type&& value) {
    auto newtop = new tds::treiber_stack<VT>::node{std::move(value)};
    newtop->next = top;

    while (!top.compare_exchange_weak(newtop->next, newtop));
    size_counter.fetch_add(1);
}

template<typename VT>
std::pair<VT, bool> tds::treiber_stack<VT>::pop() {
    node* old_top;
    {
        hazard_ptr<node> guard;
        while (true) {
            old_top = guard.protect(top);
            if (!old_top) {
                return {value_type(), false};
            }

            if(top.compare_exchange_weak(old_top, old_top->next,
               std::memory_order_acquire, std::memory_order_relaxed)) {
                break;
            }
        }
    }
    auto data = old_top->value;
    hazard_ptr<node>::retire(old_top);
    size_counter.fetch_add(-1);
    return {data, true};
}

template<typename VT>
size_t tds::treiber_stack<VT>::size() const {
    return size_counter.load();
}
