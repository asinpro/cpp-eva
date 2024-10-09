#ifndef CPP_EVA_USER_DEFINED_FUNC_TEST_H
#define CPP_EVA_USER_DEFINED_FUNC_TEST_H

#include "test_utils.h"
#include "../expression_helpers.h"
#include "../eva.h"

void runUserDefinedFuncTest(Eva& eva) {
    IASSERT(
            beg(
                    def(foo, args(),
                        4
                    ),
                    call(foo, none)
            ),
            4);

    IASSERT(
            beg(
                    def(square, args1(a),
                        mul(id(a), id(a))
                    ),
                    call(square, 2)
            ),
    4);

    IASSERT(
            beg(
                    def(calc, args2(x, y),
                        beg(
                                var(z, 30),
                                add(mul(id(x), id(y)), id(z))
                        )
                    ),
                    call(calc, 10, 20)
            ),
            230);

    IASSERT(
            beg(
                    var(value, 100),

                    def(calc, args2(x, y),
                        beg(
                                var(z, add(id(x), id(y))),

                                def(inner, args1(foo),
                                    add(add(id(foo), id(z)), id(value))
                                ),

                                id(inner)
                        )
                    ),

                    var(fn, call(calc, 10, 20)),

                    call(fn, 30)
            ),
    160);

    IASSERT(
            beg(
                    def(square, args2(a, b),
                        mul(id(a), id(a))
                    ),
                    var(x, 3),
                    call(square, id(x), "test", 2, id(square))
            ),
            9);

//    IASSERT(
//            beg(
//                    def(square, args("a"),
//                        mul(id(a), id(a))
//                    ),
//                    def(test, args("fun"),
//                        call(id(fun), 4)
//                    ),
//                    call(test, id(square))
//            ),
//            16);
}

#endif //CPP_EVA_USER_DEFINED_FUNC_TEST_H
