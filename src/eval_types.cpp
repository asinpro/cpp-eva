#include <string>
#include "eval_types.h"
#include "environment.h"

using namespace std;

EvalResult Assignment::eval(std::shared_ptr<Environment> env) const {
    const EvalResult& val = value->eval(env);
    env->define(name, val);
    return val;
}

EvalResult Identifier::eval(std::shared_ptr<Environment> env) const {
    return env->lookup(name);
}

EvalResult BinaryOperation::eval(std::shared_ptr<Environment> env) const {
    const int& lhs = get<int>(left->eval(env));
    const int& rhs = get<int>(right->eval(env));

    switch (type) {
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            return lhs / rhs;
        default:
            throw runtime_error("Unknown operation: " + string(1, type));
    }
}
