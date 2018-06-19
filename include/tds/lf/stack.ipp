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
tds::lf::stack<VT>::~stack() {
    auto curr = top.load();
    while(curr) {
        auto temp = curr->next;
        delete curr;
        curr = temp;
    }
}

template<typename VT>
void tds::lf::stack<VT>::push(value_type value) {
    auto new_top = new tds::lf::stack<VT>::node{value};
    new_top->next = top;

    while (!top.compare_exchange_weak(new_top->next, new_top,
            std::memory_order_acq_rel, std::memory_order_relaxed));
    size_counter.fetch_add(1, std::memory_order_release);
}

template<typename VT>
std::pair<VT, bool> tds::lf::stack<VT>::pop() {
    node* local_top = nullptr;
    {
        smr::hazard_ptr<node> guard;
        while (true) {
            local_top = guard.protect(top);
            if (!local_top) {
                return {value_type(), false};
            }
            if (top.compare_exchange_weak(local_top, local_top->next,
                    std::memory_order_acq_rel, std::memory_order_relaxed)) {
                break;
            }
        }
    }
    auto data = local_top->value;
    smr::hazard_ptr<node>::retire(local_top);
    size_counter.fetch_sub(1, std::memory_order_release);
    return {data, true};
}

template<typename VT>
size_t tds::lf::stack<VT>::size() const {
    return size_counter.load(std::memory_order_acquire);
}
