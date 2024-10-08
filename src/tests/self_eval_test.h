#ifndef CPP_EVA_SELF_EVAL_TEST_H
#define CPP_EVA_SELF_EVAL_TEST_H

#include <cassert>
#include "test_utils.h"
#include "../expression_helpers.h"
#include "../eva.h"

void runSelfEvalTests(Eva& eva) {
    using namespace std;

    IASSERT(lit(101), 101);
    SASSERT(lit("hello"), "hello");
}

#endif //CPP_EVA_SELF_EVAL_TEST_H