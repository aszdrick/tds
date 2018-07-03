///////////////////////////////////////////////////////////////////////////////
////////////////////////// <github.com/aszdrick/tds> //////////////////////////
//////////////////////////// <aszdrick@gmail.com> /////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018 Marleson Graf

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

template<typename VT, typename BS>
tds::lf::queue<VT,BS>::queue() {
    auto dumb_node = new node{VT()};
    head.store(dumb_node, std::memory_order_relaxed);
    tail.store(dumb_node, std::memory_order_relaxed);
}

template<typename VT, typename BS>
tds::lf::queue<VT,BS>::~queue() {
    auto curr = head.load(std::memory_order_relaxed);
    while(curr) {
        auto temp = curr->next.load(std::memory_order_relaxed);
        delete curr;
        curr = temp;
    }
}

template<typename VT, typename BS>
void tds::lf::queue<VT,BS>::push(value_type value) {
    BackOffStrategy backoff;
    auto new_node = new node{value};
    node* local_tail = nullptr;
    smr::hazard_ptr<node> guard;

    while (true) {
        local_tail = guard.protect(tail);
        auto next = local_tail->next.load(std::memory_order_relaxed);
        if (local_tail != tail) {
            continue;
        }
        if (next) {
            tail.compare_exchange_weak(local_tail, next,
                std::memory_order_acq_rel, std::memory_order_relaxed);
            continue;
        }
        if (local_tail->next.compare_exchange_weak(next, new_node,
                std::memory_order_acq_rel, std::memory_order_relaxed)) {
            break;
        } else {
            backoff();
        }
    }

    tail.compare_exchange_weak(local_tail, new_node,
        std::memory_order_acq_rel, std::memory_order_relaxed);
    size_counter.fetch_add(1, std::memory_order_release);
}

template<typename VT, typename BS>
std::pair<VT, bool> tds::lf::queue<VT,BS>::pop() {
    BackOffStrategy backoff;
    node* local_head = nullptr;
    auto data = VT();
    {
        smr::hazard_ptr<node> head_guard;
        smr::hazard_ptr<node> next_guard;

        while (true) {
            local_head = head_guard.protect(head);
            auto next = next_guard.protect(local_head->next);
            auto local_tail = tail.load(std::memory_order_relaxed);
            if (local_head != head) {
                continue;
            }
            if (!next) {
                return {data, false};
            }
            if (local_head == local_tail) {
                tail.compare_exchange_weak(local_tail, next,
                    std::memory_order_acq_rel, std::memory_order_relaxed);
                continue;
            }
            data = next->value;
            if (head.compare_exchange_weak(local_head, next,
                    std::memory_order_acq_rel, std::memory_order_relaxed)) {
                break;
            } else {
                backoff();
            }
        }
    }
    size_counter.fetch_sub(1, std::memory_order_release);
    smr::hazard_ptr<node>::retire(local_head);
    return {data, true};
}

template<typename VT, typename BS>
size_t tds::lf::queue<VT,BS>::size() const {
    return size_counter.load(std::memory_order_acquire);
}
