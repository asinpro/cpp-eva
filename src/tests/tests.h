#ifndef CPP_EVA_TESTS_H
#define CPP_EVA_TESTS_H

#include "../eva.h"
#include "self_eval_test.h"
#include "variables-test.h"
#include "math_test.h"

void runTests(Eva& eva) {
    runSelfEvalTests(eva);
    runVariablesTests(eva);
    runMathTests(eva);
    std::cerr << "All tests passed!" << std::endl;
}

#endif //CPP_EVA_TESTS_H
