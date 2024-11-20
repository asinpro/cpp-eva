#ifndef CPP_EVA_CLASS_TEST_H
#define CPP_EVA_CLASS_TEST_H

#include "../eva.h"
#include "test_utils.h"
#include "expression_helpers.h"

void runClassTest(Eva &eva)
{
    IASSERT(beg(
                cls("Point", NONE,
                    beg(
                        def("constructor", args("self", "x", "y"),
                            beg(
                                setm(prop("self", "x"), id("x")),
                                setm(prop("self", "y"), id("y")))),

                        def("calc", args("self"),
                            beg(
                                add(prop("self", "x"), prop("self", "y")))))),

                var("p", newi("Point", vars(10, 20))),
                callm(prop("p", "calc"), vars(id("p")))),
            30);
}

#endif // CPP_EVA_CLASS_TEST_H
