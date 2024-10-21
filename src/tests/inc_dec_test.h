#ifndef CPP_EVA_INC_DEC_TEST_H
#define CPP_EVA_INC_DEC_TEST_H

#include "../eva.h"
#include "test_utils.h"
#include "../expression_helpers.h"

void runIncDecTest(Eva& eva) {
    IASSERT(
            beg(
                    var(x, 10),
                    inc(x)
            )
    , 11);

    IASSERT(
            dec(10)
    ,9);
}

#endif //CPP_EVA_INC_DEC_TEST_H
