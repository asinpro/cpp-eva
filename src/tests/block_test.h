#ifndef CPP_EVA_BLOCK_TEST_H
#define CPP_EVA_BLOCK_TEST_H

#include "test_utils.h"
#include "../expression_helpers.h"
#include "../eva.h"

void runBlockTest(Eva& eva) {
    IASSERT(
            beg(
                    var(a, 10),
                    var(b, 20),
                    add(mul(id(a), id(b)), 30)
            ),
            230);

    IASSERT(
            beg(
                    var(x, 10),
                    beg(
                            var(x, 20),
                            id(x)
                    ),
                    id(x)
            ),
            10);

    IASSERT(
            beg(
                    var(value, 10),
                    var(result, beg(
                            var(x, add(id(value), 10)),
                            id(x)
                    )),
                    id(result)
            ),
            20);

    IASSERT(
            beg(
                    var(data, 10),
                    beg(
                            set(data, 100)
                    ),
                    id(data)
            ),
            100);
}


#endif //CPP_EVA_BLOCK_TEST_H
