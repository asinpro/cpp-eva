#ifndef CPP_EVA_IF_TEST_H
#define CPP_EVA_IF_TEST_H

#include "test_utils.h"
#include "expression_helpers.h"
#include "../eva.h"

void runIfTests(Eva &eva)
{
    IASSERT(
        beg(
            var("x", 10),
            var("y", lit(0)),
            iff(gt(id("x"), 10),
                set("y", 20),
                set("y", 30)),
            id("y")),
        30);
}

#endif // CPP_EVA_IF_TEST_H