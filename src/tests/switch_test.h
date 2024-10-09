#ifndef CPP_EVA_SWITCH_TEST_H
#define CPP_EVA_SWITCH_TEST_H

#include "test_utils.h"
#include "../expression_helpers.h"
#include "../eva.h"

void runSwitchTest(Eva& eva) {
    IASSERT(
            beg(
                    var(x, 10),
                    select(when(eq(id(x), 10), 100),
                           when(gt(id(x), 10), 200),
                           any(300)
                    )
            )
    ,100);

    IASSERT(
            beg(
                    var(x, 20),
                    select(when(eq(id(x), 10), 100),
                           when(gt(id(x), 10), 200),
                           any(300)
                    )
            )
    ,200);

    IASSERT(
            beg(
                    var(x, 1),
                    select(when(eq(id(x), 10), 100),
                           when(gt(id(x), 10), 200),
                           any(300)
                    )
            )
    ,300);
}

#endif //CPP_EVA_SWITCH_TEST_H
