#ifndef CPP_EVA_LAMBDA_FUNC_TEST_H
#define CPP_EVA_LAMBDA_FUNC_TEST_H

#include "test_utils.h"
#include "expression_helpers.h"
#include "../eva.h"

void runLambdaFuncTest(Eva &eva)
{
    IASSERT(
        beg(
            def("onClick", args("callback"),
                beg(
                    var("x", 10),
                    var("y", 20),
                    call("callback", add(id("x"), id("y"))))),
            call("onClick", lambda(args("data"), mul(id("data"), 10)))),
        300);

    IASSERT(
        iile(lambda(args("x"), mul(id("x"), id("x"))), 2), 4);

    IASSERT(
        beg(
            var("square", lambda(args("x"), mul(id("x"), id("x")))),
            call("square", 2)),
        4);
}

#endif // CPP_EVA_LAMBDA_FUNC_TEST_H
