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
#include "lambda_func_test.h"
#include "for_loop_test.h"
#include "switch_test.h"
#include "inc_dec_test.h"
#include "class_test.h"

void runTests(Eva& eva) {
    runSelfEvalTests(eva);
    runVariablesTests(eva);
    runBlockTest(eva);
    runMathTests(eva);
    runIfTests(eva);
    runWhileTests(eva);
    runBuildInFunTest(eva);
    runUserDefinedFuncTest(eva);
    runLambdaFuncTest(eva);
    runForLoopTest(eva);
    runSwitchTest(eva);
    runIncDecTest(eva);
    runClassTest(eva);

    eva.eval(print("Hello", " ", "World"));

    std::cerr << "All tests passed!" << std::endl;
}

#endif //CPP_EVA_TESTS_H
