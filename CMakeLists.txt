cmake_minimum_required(VERSION 3.16.3)
project(cpp_eva)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_eva src/main.cpp
        src/eva.cpp
        src/eva.h
        src/environment.cpp
        src/environment.h
        src/tests/self_eval_test.h
        src/tests/variables-test.h
        src/eval_types.h
        src/tests/test_utils.h
        src/tests/math_test.h
        src/tests/tests.h
        src/tests/if_test.h
        src/tests/expression_helpers.h
        src/expressions.h
        src/expressions.cpp
        src/tests/while_test.h
        src/tests/block_test.h
        src/tests/built_in_func_test.h
        src/tests/user_defined_func_test.h
        src/tests/lambda_func_test.h
        src/tests/for_loop_test.h
        src/tests/switch_test.h
        src/tests/inc_dec_test.h
        src/tests/class_test.h)
