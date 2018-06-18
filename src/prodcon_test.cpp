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

#include "dsc/prodcon_precise.hpp"
#include "dsc/prodcon_sum.hpp"
#include "tds/mutexed_queue.hpp"
#include "tds/mutexed_stack.hpp"
#include "tds/treiber_stack.hpp"

void print_usage() {
    std::cout << "usage:\n"
              << "prodcon-test [type] [structure] [n_producers] [n_consumers]"
              << " [n_iterations] [random_seed] [max_gen_value]\n\n"
              << "type: 'sum', 'precise'\n"
              << "structure: 'dual_mutex_queue', mutexed_queue', "
              << "'mutexed_stack', 'treiber_stack'\n"
              << "n_producers: unsigned integer\n"
              << "n_consumers: unsigned integer\n"
              << "n_iterations: unsigned integer\n"
              << "random_seed: unsigned integer\n\n"
              << "max_gen_value: unsigned integer\n\n"
              << "usage example:\n"
              << "./prodcon-test precise treiber_stack 4 4 100000 42 100"
              << std::endl;
}

void error(const std::string& message) {
    std::cout << "error: " << message << "\n\n";
    print_usage();
    exit(1);
}

template<typename Checker>
void execute(unsigned np, unsigned nc, unsigned ni, unsigned s, unsigned m) {
    Checker checker(np, nc, m);

    if (checker.run(ni, s)) {
        std::cout << "No errors found!" << std::endl;
    } else {
        std::cout << "Execution ended with inconsistent state." << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 8) {
        error("missing options!");
    }

    auto type = std::string(argv[1]);
    auto structure = std::string(argv[2]);

    if (type == "sum") {
        if (structure == "dual_mutex_queue") {
            execute<dsc::prodcon_sum<tds::dual_mutex_queue>>(
                atol(argv[3]), atol(argv[4]), atol(argv[5]),
                atol(argv[6]), atol(argv[7])
            );
        } else if (structure == "mutexed_queue") {
            execute<dsc::prodcon_sum<tds::mutexed_queue>>(
                atol(argv[3]), atol(argv[4]), atol(argv[5]),
                atol(argv[6]), atol(argv[7])
            );
        } else if (structure == "mutexed_stack") {
            execute<dsc::prodcon_sum<tds::mutexed_stack>>(
                atol(argv[3]), atol(argv[4]), atol(argv[5]),
                atol(argv[6]), atol(argv[7])
            );
        } else if (structure == "treiber_stack") {
            execute<dsc::prodcon_sum<tds::treiber_stack>>(
                atol(argv[3]), atol(argv[4]), atol(argv[5]),
                atol(argv[6]), atol(argv[7])
            );
        } else {
            error("unkown structure!");
        }
    } else if (type == "precise") {
        if (structure == "dual_mutex_queue") {
            execute<dsc::prodcon_precise<tds::dual_mutex_queue>>(
                atol(argv[3]), atol(argv[4]), atol(argv[5]),
                atol(argv[6]), atol(argv[7])
            );
        } else if (structure == "mutexed_queue") {
            execute<dsc::prodcon_precise<tds::mutexed_queue>>(
                atol(argv[3]), atol(argv[4]), atol(argv[5]),
                atol(argv[6]), atol(argv[7])
            );
        } else if (structure == "mutexed_stack") {
            execute<dsc::prodcon_precise<tds::mutexed_stack>>(
                atol(argv[3]), atol(argv[4]), atol(argv[5]),
                atol(argv[6]), atol(argv[7])
            );
        } else if (structure == "treiber_stack") {
            execute<dsc::prodcon_precise<tds::treiber_stack>>(
                atol(argv[3]), atol(argv[4]), atol(argv[5]),
                atol(argv[6]), atol(argv[7])
            );
        } else {
            error("unkown structure!");
        }
    } else {
        error("unkown type!");
    }

    return 0;
}
