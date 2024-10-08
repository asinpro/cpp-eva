#ifndef CPP_EVA_TESTS_H
#define CPP_EVA_TESTS_H

#include "../eva.h"
#include "self_eval_test.h"
#include "variables-test.h"
#include "block_test.h"
#include "math_test.h"
#include "if_test.h"
#include "while_test.h"
#include "built_in_func_test.h"
#include "user_defined_func_test.h"

void runTests(Eva& eva) {
    runSelfEvalTests(eva);
    runVariablesTests(eva);
    runBlockTest(eva);
    runMathTests(eva);
    runIfTests(eva);
    runWhileTests(eva);
    runBuildInFunTest(eva);
    runUserDefinedFuncTest(eva);

    eva.eval(print("Hello", " ", "World"));

    std::cerr << "All tests passed!" << std::endl;
}

#endif //CPP_EVA_TESTS_H
