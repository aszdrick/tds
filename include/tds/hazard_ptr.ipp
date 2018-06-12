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
template<unsigned N, unsigned K>
std::array<typename tds::detail::hp_context<N,K>::entry, N*K>
tds::detail::hp_context<N,K>::guard_entries;

template<typename T, unsigned N, unsigned K>
thread_local typename tds::hazard_ptr<T,N,K>::container
tds::hazard_ptr<T,N,K>::retired;

///////////////////////////////////////////////////////////////////////////////
// tds::detail::hp_context<K,N>::container methods implementation
///////////////////////////////////////////////////////////////////////////////

// template<typename T, unsigned N, unsigned K>
// tds::hazard_ptr<T,N,K>::container::container() {
//     objects.reserve(N*K*2);
// }

template<typename T, unsigned N, unsigned K>
tds::hazard_ptr<T,N,K>::container::~container() {
    while (!objects.empty()) {
        detail::hp_context<N,K>::scan(objects);
    }
}

///////////////////////////////////////////////////////////////////////////////
// tds::detail::hp_context methods implementation
///////////////////////////////////////////////////////////////////////////////

template<unsigned N, unsigned K>
unsigned tds::detail::hp_context<N,K>::guard() noexcept {
    unsigned index;
    for (index = 0; index < N*K; ++index) {
        bool empty_entry = false;
        if (!guard_entries[index].second.load(std::memory_order_relaxed) &&
                guard_entries[index].second.compare_exchange_strong(
                    empty_entry, true)) {
            break;
        }
    }
    assert(index != N*K);
    return index;
}

template<unsigned N, unsigned K>
void tds::detail::hp_context<N,K>::release(unsigned index) noexcept {
    guard_entries[index].first = nullptr;
    guard_entries[index].second = false;
}

template<unsigned N, unsigned K>
template<typename Ptr>
Ptr tds::detail::hp_context<N,K>::protect(const std::atomic<Ptr>& value,
                                          unsigned index) noexcept {
    Ptr copy;
    do {
        copy = value.load(std::memory_order_relaxed);
        guard_entries[index].first = copy;
    } while (copy != value.load(std::memory_order_relaxed));
    return copy;
}

template<unsigned N, unsigned K>
template<typename Ptr>
void tds::detail::hp_context<N,K>::scan(std::vector<Ptr>& objects) {
    std::unordered_set<Ptr> to_be_deleted(
        objects.cbegin(), objects.cend()
    );
    objects.clear();
    for (unsigned i = 0; i < N*K; ++i) {
        if (guard_entries[i].second.load(std::memory_order_relaxed)) {
            auto pointer = reinterpret_cast<Ptr>(guard_entries[i].first);
            if(to_be_deleted.erase(pointer)) {
                objects.push_back(pointer);
            }
        }
    }
    for (auto pointer : to_be_deleted) {
        delete pointer;
    }
}

///////////////////////////////////////////////////////////////////////////////
// tds::hazard_ptr methods implementation
///////////////////////////////////////////////////////////////////////////////

template<typename T, unsigned N, unsigned K>
tds::hazard_ptr<T,N,K>::hazard_ptr() noexcept {
    guard_id = detail::hp_context<N,K>::guard();
}

template<typename T, unsigned N, unsigned K>
T* tds::hazard_ptr<T,N,K>::protect(const std::atomic<T*>& value) noexcept {
    return detail::hp_context<N,K>::protect(value, guard_id);
}

template<typename T, unsigned N, unsigned K>
tds::hazard_ptr<T,N,K>::~hazard_ptr() noexcept {
    detail::hp_context<N,K>::release(guard_id);
}

template<typename T, unsigned N, unsigned K>
void tds::hazard_ptr<T,N,K>::retire(T* obj_ptr) noexcept {
    retired.objects.push_back(obj_ptr);
    if (retired.objects.size() > RETIRED_LIMIT) {
        detail::hp_context<N,K>::scan(retired.objects);
    }
}
