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

///////////////////////////////////////////////////////////////////////////////
// tds::lb::queue
///////////////////////////////////////////////////////////////////////////////

template<typename VT>
void tds::lb::queue<VT>::push(value_type value) {
    std::lock_guard<std::mutex> guard(mutex);
    inner_queue.push(std::move(value));
}

template<typename VT>
std::pair<VT, bool> tds::lb::queue<VT>::pop() {
    std::lock_guard<std::mutex> guard(mutex);
    if (!inner_queue.empty()) {
        auto temp = inner_queue.front();
        inner_queue.pop();
        return {temp, true};
    }
    return {0, false};
}

template<typename VT>
size_t tds::lb::queue<VT>::size() const { 
    return inner_queue.size();
}

///////////////////////////////////////////////////////////////////////////////
// tds::lb::dual_lock_queue
///////////////////////////////////////////////////////////////////////////////

template<typename VT>
tds::lb::dual_lock_queue<VT>::dual_lock_queue() {
    head = new node{VT(), nullptr};
    tail = head;
}

template<typename VT>
tds::lb::dual_lock_queue<VT>::~dual_lock_queue() {
    auto it = head;
    while(it) {
        auto d = it;
        it = it->next;
        delete d;
    }
}

template<typename VT>
void tds::lb::dual_lock_queue<VT>::push(value_type value) {
    std::lock_guard<std::mutex> guard(push_mutex);
    auto new_node = new node{std::move(value), nullptr};
    tail->next = new_node;
    tail = new_node;
    size_counter.fetch_add(1);
}

template<typename VT>
std::pair<VT, bool> tds::lb::dual_lock_queue<VT>::pop() {
    std::lock_guard<std::mutex> guard(pop_mutex);
    if (!head->next) {
        return {VT(), false};
    }
    auto old_head = head;
    head = head->next;
    auto value = head->value;
    delete old_head;
    size_counter.fetch_sub(1);
    return {value, true};
}

template<typename VT>
size_t tds::lb::dual_lock_queue<VT>::size() const { 
    return size_counter;
}
