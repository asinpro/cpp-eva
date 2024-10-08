#include "expressions.h"

#include <string>
#include "eval_types.h"
#include "environment.h"

using namespace std;

EvalResult VariableDeclaration::eval(std::shared_ptr<Environment> env) const {
    const EvalResult& val = value->eval(env);
    env->define(name, val);
    return val;
}

EvalResult Assignment::eval(std::shared_ptr<Environment> env) const {
    return env->assign(name, value->eval(env));
}

EvalResult Identifier::eval(std::shared_ptr<Environment> env) const {
    return env->lookup(name);
}

EvalResult BinaryOperation::eval(std::shared_ptr<Environment> env) const {
    const int lhs = get<int>(left->eval(env));
    const int rhs = get<int>(right->eval(env));

    switch (type) {
        case '+':
            return lhs + rhs;
        case '-':
            return lhs - rhs;
        case '*':
            return lhs * rhs;
        case '/':
            return lhs / rhs;
        case '>':
            return lhs > rhs;
        case '<':
            return lhs < rhs;
        case '=':
            return lhs == rhs;
        default:
            throw runtime_error("Unknown operation: " + string(1, type));
    }
}

EvalResult Block::eval(std::shared_ptr<Environment> env) const {
    EvalMap vars;
    auto blockEnv = make_shared<Environment>(vars, env);

    EvalResult result;
    for (const auto& exp : expressions) {
        result = exp->eval(blockEnv);
    }
    return result;
}

EvalResult Condition::eval(std::shared_ptr<Environment> env) const {
    if (get<bool>(condition->eval(env))) {
        return then->eval(env);
    } else {
        return otherwise->eval(env);
    }
}

EvalResult Loop::eval(std::shared_ptr<Environment> env) const {
    EvalResult result;
    while (get<bool>(condition->eval(env))) {
        result = body->eval(env);
    }
    return result;
}

EvalResult FunctionDefinition::eval(std::shared_ptr<Environment> env) const {
    env->define(name, Function(name, params, body, env));
    return Null{};
}

EvalResult FunctionCall::eval(std::shared_ptr<Environment> env) const {
    const auto fun = get<Function>(env->lookup(name));
    auto funEnv = make_shared<Environment>(EvalMap{}, fun.env);

    for (size_t i = 0; i < fun.params.size(); ++i) {
        funEnv->define(fun.params[i], args[i]->eval(env));
    }

    return fun.body->eval(funEnv);
}
