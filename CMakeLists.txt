cmake_minimum_required(VERSION 3.29.6)
project(cpp_eva)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_eva src/main.cpp
        src/eva.cpp
        src/eva.h
        src/environment.cpp
        src/environment.h
        src/transformer.cpp
        src/transformer.h
        src/tests/self_eval_test.h
        src/tests/variables-test.h
        src/eval_types.h
        src/tests/test_utils.h
        src/tests/math_test.h
        src/tests/tests.h
        src/eval_types.cpp)
