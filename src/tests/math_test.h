#ifndef CPP_EVA_MATH_TEST_H
#define CPP_EVA_MATH_TEST_H

#include "test_utils.h"
#include "../eva.h"

void runMathTests(Eva& eva) {
    using namespace std;

    IASSERT(add(2, 3), 5);
    IASSERT(sub(10, 3), 7);
    IASSERT(mul(2, 3), 6);
    IASSERT(diw(10, 3), 3);
//    IASSERT($(% 10 3), 1);
}

#endif //CPP_EVA_MATH_TEST_H
