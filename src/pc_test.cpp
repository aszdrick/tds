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
#include "tds/lb/queue.hpp"
#include "tds/lb/stack.hpp"
#include "tds/lf/queue.hpp"
#include "tds/lf/stack.hpp"

void print_usage() {
    std::cout << "usage:\n"
              << "prodcon-test [test_type] [sync_type] [structure] "
              << "[n_producers] [n_consumers] [n_productions] [random_seed] "
              << "[max_gen_value]\n\n"
              << "test_type: 'sum', 'precise'\n"
              << "sync_type: 'lf, lb"
              << "structure: 'dual_lock_queue', 'queue', 'stack'\n"
              << "n_producers: unsigned integer\n"
              << "n_consumers: unsigned integer\n"
              << "n_productions: unsigned integer\n"
              << "random_seed: unsigned integer\n\n"
              << "max_gen_value: unsigned integer\n\n"
              << "usage example:\n"
              << "./prodcon-test precise lf stack 4 4 100000 42 100"
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

template<template<template<class> class> class TestType>
void define_structure(char** argv) {
    auto sync_type = std::string(argv[2]);
    auto structure = std::string(argv[3]);

    if (sync_type == "lb") {
        if (structure == "dual_lock_queue") {
            execute<TestType<tds::lb::dual_lock_queue>>(
                atol(argv[4]), atol(argv[5]), atol(argv[6]),
                atol(argv[7]), atol(argv[8])
            );
        } else if (structure == "queue") {
            execute<TestType<tds::lb::queue>>(
                atol(argv[4]), atol(argv[5]), atol(argv[6]),
                atol(argv[7]), atol(argv[8])
            );
        } else if (structure == "stack") {
            execute<TestType<tds::lb::stack>>(
                atol(argv[4]), atol(argv[5]), atol(argv[6]),
                atol(argv[7]), atol(argv[8])
            );
        } else {
            error("unkown structure!");
        }
    } else if (sync_type == "lf") {
        if (structure == "queue") {
            execute<TestType<tds::lf::queue>>(
                atol(argv[4]), atol(argv[5]), atol(argv[6]),
                atol(argv[7]), atol(argv[8])
            );
        } else if (structure == "stack") {
            execute<TestType<tds::lf::stack>>(
                atol(argv[4]), atol(argv[5]), atol(argv[6]),
                atol(argv[7]), atol(argv[8])
            );
        } else if (structure == "dual_lock_queue") {
            error("invalid structure for lf sync_type!");
        } else {
            error("unkown structure!");
        }
    } else {
        error("unkown sync_type!");
    }
}

int main(int argc, char** argv) {
    if (argc < 9) {
        error("missing options!");
    }

    auto test_type = std::string(argv[1]);

    if (test_type == "sum") {
        define_structure<dsc::prodcon_sum>(argv);
    } else if (test_type == "precise") {
        define_structure<dsc::prodcon_precise>(argv);
    } else {
        error("unkown test_type!");
    }

    return 0;
}
