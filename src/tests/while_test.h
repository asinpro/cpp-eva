#ifndef CPP_EVA_WHILE_TEST_H
#define CPP_EVA_WHILE_TEST_H

#include "test_utils.h"
#include "expression_helpers.h"
#include "../eva.h"

void runWhileTests(Eva &eva)
{
    IASSERT(
        beg(
            var("counter", lit(0)),
            var("result", lit(0)),
            loop(
                lt(id("counter"), 10),
                beg(
                    set("result", add(id("result"), 1)),
                    set("counter", add(id("counter"), 1)))),
            id("result")),
        10);
}

#endif // CPP_EVA_WHILE_TEST_H
