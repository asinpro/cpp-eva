#ifndef CPP_EVA_MATH_TEST_H
#define CPP_EVA_MATH_TEST_H

#include "test_utils.h"
#include "expression_helpers.h"
#include "../eva.h"

void runMathTests(Eva &eva)
{
    IASSERT(add(2, 3), 5);
    IASSERT(sub(10, 3), 7);
    IASSERT(mul(2, 3), 6);
    IASSERT(divv(10, 3), 3);
}

#endif // CPP_EVA_MATH_TEST_H
