#ifndef CPP_EVA_FOR_LOOP_TEST_H
#define CPP_EVA_FOR_LOOP_TEST_H

#include "test_utils.h"
#include "../expression_helpers.h"
#include "../eva.h"

void runForLoopTest(Eva& eva) {
    IASSERT(
            beg(
                    var(sum, lit(0)),
                    floop(var(x, 10),
                          gt(id(x), 0),
                          set(x, sub(id(x), 1)),
                          beg(
                                  set(sum, add(id(sum), 1))
                          )
                    ),
                    id(sum)
            )
    ,10);
}

#endif //CPP_EVA_FOR_LOOP_TEST_H
