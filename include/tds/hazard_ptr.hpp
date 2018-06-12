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

#ifndef __TDS_HAZARD_PTR_HPP__
#define __TDS_HAZARD_PTR_HPP__

#include <array>
#include <atomic>
#include <cassert>
#include <cstdint>
#include <future>
#include <unordered_set>
#include <thread>
#include <utility>
#include <vector>

// Thread-safe Data Structures
namespace tds {
    // Namespace detail contains definitions that should not be used
    // outside the hazard_ptr class.
    namespace detail {
        // Hazard Pointers Context:
        // Responsible for the actual memory reclamation.
        // Keeps a per thread list of 'retired' objects to be deleted
        // and a global list of 'protected' objects.
        template<unsigned N, unsigned K>
        class hp_context {
            // Entry used in the guard_entries.
            // Stores each pointer as void* and uses an atomic_bool
            // to sinalize activation and deactivation.
            using entry = std::pair<void*, std::atomic_bool>;
         public:
            template<typename T>
            using list_type = std::vector<T>;
            // Activates a guard entry in guard_entries
            // and returns the corresponding id.
            static unsigned guard() noexcept;
            // Protects an atomic value in the given guard_id.
            // The returned value is guaranteed to be protected.
            template<typename Ptr>
            static Ptr protect(const std::atomic<Ptr>&, unsigned) noexcept;
            // Deactivates the guard entry in the passed guard_id.
            static void release(unsigned) noexcept;
            // Scans the objects stored in retired.objects and deletes those
            // which are not present in guard_entries.
            template<typename Ptr>
            static void scan(list_type<Ptr>&);
         private:
            static std::array<entry, N*K> guard_entries;
        };
    }

    template<typename T, unsigned N, unsigned K = 1>
    class hazard_ptr {
        // Limit used to decide when make a new call to scan().
        static constexpr auto RETIRED_LIMIT = N*K*2;
        // Container to hold the retired objects.
        // It's required to ensure the deletion of retired objects
        // in the event of destruction of the owner thread.
        struct container {
            // container();
            ~container();
            typename detail::hp_context<N,K>::template list_type<T*> objects;
        };
     public:
        hazard_ptr() noexcept;
        hazard_ptr(const hazard_ptr<T,N,K>&) = delete;
        hazard_ptr(hazard_ptr<T,N,K>&&) = delete;

        ~hazard_ptr() noexcept;
        // Retires a value, placing it in the retired.objects vector.
        // Also makes a call to scan() if RETIRED_LIMIT is reached.
        static void retire(T* value_ptr) noexcept;

        T* protect(const std::atomic<T*>&) noexcept;
     private:
        unsigned guard_id;
        static thread_local container retired;
    };
}

#include "hazard_ptr.ipp"

#endif /* __TDS_HAZARD_PTR_HPP__ */
