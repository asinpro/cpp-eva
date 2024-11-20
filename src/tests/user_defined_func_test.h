#ifndef CPP_EVA_USER_DEFINED_FUNC_TEST_H
#define CPP_EVA_USER_DEFINED_FUNC_TEST_H

#include "test_utils.h"
#include "expression_helpers.h"
#include "../eva.h"

void runUserDefinedFuncTest(Eva &eva)
{
    IASSERT(
        beg(
            def("foo", args(), 4),
            call("foo", none)),
        4);

    IASSERT(
        beg(
            def("square", args("a"),
                mul(id("a"), id("a"))),
            call("square", 2)),
        4);

    IASSERT(
        beg(
            def("calc", args("x", "y"),
                beg(
                    var("z", 30),
                    add(mul(id("x"), id("y")), id("z")))),
            call("calc", 10, 20)),
        230);

    IASSERT(
        beg(
            var("value", 100),

            def("calc", args("x", "y"),
                beg(
                    var("z", add(id("x"), id("y"))),
                    add(mul(id("x"), id("y")), id("z")))),
            call("calc", 10, 20)),
        230);
}

#endif // CPP_EVA_USER_DEFINED_FUNC_TEST_H
