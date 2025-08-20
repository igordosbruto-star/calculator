#pragma once

#include <initializer_list>

using TestFunc = void(*)();

inline int run_tests(std::initializer_list<TestFunc> tests) {
    for (auto test : tests) {
        test();
    }
    return 0;
}
