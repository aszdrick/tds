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

#ifndef __SMR_HAZARD_PTR_HPP__
#define __SMR_HAZARD_PTR_HPP__

#include <array>
#include <atomic>
#include <cassert>
#include <cstdint>
#include <future>
#include <unordered_set>
#include <thread>
#include <utility>
#include <vector>

// Safe Memory Reclamation
namespace smr {
    // Namespace detail contains definitions that should not be used
    // outside the hazard_ptr class.
    namespace detail {
        struct hazard_list {
            struct entry {
                void* pointer = nullptr;
                entry* next = nullptr;
                std::atomic_bool active{false};
            };

            ~hazard_list();

            std::atomic<entry*> head{nullptr};
            std::atomic_uint size{0};
        };
        // Hazard Pointers Context:
        // Responsible for the actual memory reclamation.
        // Keeps a per thread list of 'retired' objects to be deleted
        // and a global list of 'protected' objects.
        class hp_context {
         public:
            template<typename T>
            using list_type = std::vector<T>;
            // Activates a hazard entry in hazard_entries
            // and returns the corresponding entry reference.
            static hazard_list::entry& acquire();
            // Protects an atomic value in the given guard_id.
            // The returned value is guaranteed to be protected.
            template<typename Ptr>
            static Ptr protect(const std::atomic<Ptr>&, unsigned);
            // Deactivates the guard entry in the passed guard_id.
            static void release(unsigned);
            // Scans the objects stored in retired.objects and deletes those
            // which are not present in hazard_entries.
            template<typename Ptr>
            static void scan(list_type<Ptr>&);

            static unsigned size();
         private:
            static hazard_list hazard_entries;
        };
    }

    template<typename T>
    class hazard_ptr {
        // Container to hold the retired objects.
        // It's required to ensure the deletion of retired objects
        // in the event of destruction of the owner thread.
        struct container {
            ~container();
            typename detail::hp_context::list_type<T*> objects;
        };
     public:
        hazard_ptr();
        hazard_ptr(const hazard_ptr<T>&) = delete;
        hazard_ptr(hazard_ptr<T>&&) = delete;

        ~hazard_ptr();
        // Retires a value, placing it in the retired.objects vector.
        // Also makes a call to scan() if RETIRED_LIMIT is reached.
        static void retire(T* value_ptr);

        T* protect(const std::atomic<T*>&);
     private:
        detail::hazard_list::entry& hazard_entry;
        static thread_local container retired;
    };
}

#include "hazard_ptr.ipp"

#endif /* __SMR_HAZARD_PTR_HPP__ */
