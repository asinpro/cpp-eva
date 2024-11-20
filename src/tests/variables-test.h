#ifndef CPP_EVA_VARIABLES_TEST_H
#define CPP_EVA_VARIABLES_TEST_H

#include "test_utils.h"
#include "expression_helpers.h"
#include "../eva.h"

void runVariablesTests(Eva &eva)
{
    using namespace std;

    // Define a variable
    IASSERT(var("x", 10), 10);
    IASSERT(id("x"), 10);
    SASSERT(id("VERSION"), "0.1"s);

    NASSERT(var("none", NONE));
    BASSERT(var("isUser", TRUE), true);
    BASSERT(var("isAuth", FALSE), false);

    IASSERT(var("z", mul(2, 2)), 4);
    IASSERT(id("z"), 4);
}

#endif // CPP_EVA_VARIABLES_TEST_H
