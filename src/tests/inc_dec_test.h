#ifndef CPP_EVA_INC_DEC_TEST_H
#define CPP_EVA_INC_DEC_TEST_H

#include "../eva.h"
#include "test_utils.h"
#include "expression_helpers.h"

void runIncDecTest(Eva &eva)
{
    IASSERT(
        beg(
            var("x", 10),
            inc(id("x"))),
        11);

    IASSERT(
        beg(
            var("y", 10),
            dec(id("y"))),
        9);
}

#endif // CPP_EVA_INC_DEC_TEST_H
