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

#include <cstdlib>
#include <iostream>

#include "dsb/prodcon.hpp"
#include "tds/lb/queue.hpp"
#include "tds/lb/stack.hpp"
#include "tds/lf/queue.hpp"
#include "tds/lf/stack.hpp"

namespace tds { namespace lf {
    template<typename T>
    using stack_ebs = stack<T, bs::exponential>;
    template<typename T>
    using stack_nbs = stack<T, bs::no_backoff>;
    template<typename T>
    using queue_ebs = queue<T, bs::exponential>;
    template<typename T>
    using queue_nbs = queue<T, bs::no_backoff>;
}}

void print_usage() {
    std::cout << "usage:\n"
              << "pc-bench [sync_type] [structure] [backoff] [n_producers] "
              << "[n_consumers] [n_productions] [random_seed] [produce_delay]"
              << " [consume_delay]\n\n"
              << "sync_type: 'lf, lb"
              << "structure: 'dual_lock_queue', 'queue', 'stack'\n"
              << "backoff: 'none', 'exponential'\n"
              << "n_producers: unsigned integer\n"
              << "n_consumers: unsigned integer\n"
              << "n_productions: unsigned integer\n"
              << "random_seed: unsigned integer\n\n"
              << "produce_delay: unsigned integer (nanoseconds)\n\n"
              << "consume_delay: unsigned integer (nanoseconds)\n\n"
              << "usage example:\n"
              << "./pc-bench lf stack none 4 4 100000 42 100 100"
              << std::endl;
}

void error(const std::string& message) {
    std::cout << "error: " << message << "\n\n";
    print_usage();
    exit(1);
}

template<typename Benchmark>
void execute(unsigned np, unsigned nc, unsigned ni, unsigned s, unsigned pd,
             unsigned cd) {
    Benchmark bench(np, nc, pd, cd);
    bench.run(ni, s);
}

int main(int argc, char** argv) {
    if (argc < 10) {
        error("missing options!");
    }

    auto sync_type = std::string(argv[1]);
    auto structure = std::string(argv[2]);
    auto backoff = std::string(argv[3]);

    if (sync_type == "lb") {
        if (backoff == "none") {
            if (structure == "dual_lock_queue") {
                execute<dsb::prodcon<tds::lb::dual_lock_queue>>(
                    atol(argv[4]), atol(argv[5]), atol(argv[6]), atol(argv[7]),
                    atol(argv[8]), atol(argv[9])
                );
            } else if (structure == "queue") {
                execute<dsb::prodcon<tds::lb::queue>>(
                    atol(argv[4]), atol(argv[5]), atol(argv[6]), atol(argv[7]),
                    atol(argv[8]), atol(argv[9])
                );
            } else if (structure == "stack") {
                execute<dsb::prodcon<tds::lb::stack>>(
                    atol(argv[4]), atol(argv[5]), atol(argv[6]), atol(argv[7]),
                    atol(argv[8]), atol(argv[9])
                );
            } else {
                error("unkown structure!");
            }
        } else {
            error("lock-based data structures do not support"
                  " backoff (use none)");
        }
    } else if (sync_type == "lf") {
        if (structure == "queue") {
            if (backoff == "none") {
                execute<dsb::prodcon<tds::lf::queue_nbs>>(
                    atol(argv[4]), atol(argv[5]), atol(argv[6]), atol(argv[7]),
                    atol(argv[8]), atol(argv[9])
                );
            } else if (backoff == "exponential") {
                execute<dsb::prodcon<tds::lf::queue_ebs>>(
                    atol(argv[4]), atol(argv[5]), atol(argv[6]), atol(argv[7]),
                    atol(argv[8]), atol(argv[9])
                );
            } else {
                error("unkown backoff strategy!");
            }
        } else if (structure == "stack") {
            if (backoff == "none") {
                execute<dsb::prodcon<tds::lf::stack_nbs>>(
                    atol(argv[4]), atol(argv[5]), atol(argv[6]), atol(argv[7]),
                    atol(argv[8]), atol(argv[9])
                );
            } else if (backoff == "exponential") {
                execute<dsb::prodcon<tds::lf::stack_ebs>>(
                    atol(argv[4]), atol(argv[5]), atol(argv[6]), atol(argv[7]),
                    atol(argv[8]), atol(argv[9])
                );
            } else {
                error("unkown backoff strategy!");
            }
        } else if (structure == "dual_lock_queue") {
            error("invalid structure for lf sync_type!");
        } else {
            error("unkown structure!");
        }
    } else {
        error("unkown sync_type!");
    }

    return 0;
}
