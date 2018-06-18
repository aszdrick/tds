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
// Static fields initialization 
///////////////////////////////////////////////////////////////////////////////

// hp_context
tds::detail::hazard_list tds::detail::hp_context::hazard_entries;

template<typename T>
thread_local typename tds::hazard_ptr<T>::container
tds::hazard_ptr<T>::retired;

///////////////////////////////////////////////////////////////////////////////
// tds::detail::hazard_list methods implementation
///////////////////////////////////////////////////////////////////////////////

tds::detail::hazard_list::~hazard_list() {
    auto p = head.load(std::memory_order_relaxed);
    while (p) {
        auto temp = p;
        p = p->next;
        delete temp;
    }
}

///////////////////////////////////////////////////////////////////////////////
// tds::detail::hp_context methods implementation
///////////////////////////////////////////////////////////////////////////////

tds::detail::hazard_list::entry& tds::detail::hp_context::acquire() {
    auto e = hazard_entries.head.load(std::memory_order_relaxed);
    for (; e ; e = e->next) {
        auto free = false;
        if (e->active || !e->active.compare_exchange_strong(free, true)) {
            continue;
        }
        return *e;
    }

    e = new hazard_list::entry{nullptr, hazard_entries.head};
    e->active.store(true, std::memory_order_relaxed);
    while(!hazard_entries.head.compare_exchange_weak(e->next, e,
           std::memory_order_acq_rel, std::memory_order_relaxed));

    hazard_entries.size.fetch_add(1);

    return *e;
}

template<typename Ptr>
void tds::detail::hp_context::scan(std::vector<Ptr>& objects) {
    std::unordered_set<Ptr> to_be_deleted(
        objects.cbegin(), objects.cend()
    );
    objects.clear();
    auto e = hazard_entries.head.load(std::memory_order_relaxed);
    for (; e; e = e->next) {
        if (e->active.load(std::memory_order_relaxed)) {
            auto pointer = reinterpret_cast<Ptr>(e->pointer);
            if(to_be_deleted.erase(pointer)) {
                objects.push_back(pointer);
            }
        }
    }
    for (auto pointer : to_be_deleted) {
        delete pointer;
    }
}

unsigned tds::detail::hp_context::size() {
    return hazard_entries.size.load(std::memory_order_acquire);
}

///////////////////////////////////////////////////////////////////////////////
// tds::hazard_ptr::container methods implementation
///////////////////////////////////////////////////////////////////////////////

template<typename T>
tds::hazard_ptr<T>::container::~container() {
    while (!objects.empty()) {
        detail::hp_context::scan(objects);
    }
}

///////////////////////////////////////////////////////////////////////////////
// tds::hazard_ptr methods implementation
///////////////////////////////////////////////////////////////////////////////

template<typename T>
tds::hazard_ptr<T>::hazard_ptr() :
 hazard_entry{detail::hp_context::acquire()} { }

template<typename T>
T* tds::hazard_ptr<T>::protect(const std::atomic<T*>& value) {
    T* copy;
    do {
        copy = value.load(std::memory_order_relaxed);
        hazard_entry.pointer = copy;
    } while (copy != value.load(std::memory_order_relaxed));
    return copy;
}

template<typename T>
tds::hazard_ptr<T>::~hazard_ptr() {
    hazard_entry.pointer = nullptr;
    hazard_entry.active.store(false, std::memory_order_relaxed);
}

template<typename T>
void tds::hazard_ptr<T>::retire(T* obj_ptr) {
    retired.objects.push_back(obj_ptr);
    if (retired.objects.size() > 2 * detail::hp_context::size()) {
        detail::hp_context::scan(retired.objects);
    }
}
