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

#include "dsc/prodcon_sum.hpp"
#include "dsc/prodcon_precise.hpp"
#include "tds/mutexed_stack.hpp"
#include "tds/treiber_stack.hpp"

int main(int argc, char** argv) {
    if (argc < 6) {
        std::cout << "usage: tds-test [type] [n_producers]"
                  << " [n_consumers] [n_iterations] [random_seed]"
                  << std::endl;
        return 1;
    }

    int result = -1;
    auto type = std::string(argv[1]);

    if (type == "mutexed_stack") {
        dsc::prodcon_precise<tds::mutexed_stack> checker(
            atoll(argv[2]), atoll(argv[3])
        );

        result = checker.run(atoll(argv[4]), atoll(argv[5]));
    } else if (type == "treiber_stack") {
        dsc::prodcon_precise<tds::treiber_stack> checker(
            atoll(argv[2]), atoll(argv[3])
        );

        result = checker.run(atoll(argv[4]), atoll(argv[5]));
    }


    std::cout << result << std::endl;
    return result;
}
