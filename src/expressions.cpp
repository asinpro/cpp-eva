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

EvalResult FunctionDeclaration::eval(std::shared_ptr<Environment> env) const {
    // JIT-transpile to variable declaration

    auto _this = const_cast<FunctionDeclaration*>(this);
    auto lambda = Lambda::create(params, std::move(_this->body));

    auto value = lambda->eval(env);
    env->define(name, value);
    return value;
}

Function FunctionCall::resolveFunction(std::shared_ptr<Environment> env) const {
    return get<Function>(env->lookup(name));
}

EvalResult Lambda::eval(std::shared_ptr<Environment> env) const {
    auto _this = const_cast<Lambda*>(this);
    return Function(name, params, move(_this->body), env);
}

EvalResult AnonymousFunctionCall::eval(std::shared_ptr<Environment> env) const {
    const auto fun = resolveFunction(env);
    auto funEnv = make_shared<Environment>(EvalMap{}, fun.env);

    for (size_t i = 0; i < fun.params.size(); ++i) {
        funEnv->define(fun.params[i], args[i]->eval(env));
    }

    return fun.body->eval(funEnv);
}

Function AnonymousFunctionCall::resolveFunction(std::shared_ptr<Environment> env) const {
    return get<Function>(function->eval(nullptr));
}

EvalResult ForLoop::eval(std::shared_ptr<Environment> env) const {
    // JIT-transpile to while loop

    auto _ = init->eval(env);
    auto _this = const_cast<ForLoop*>(this);

    vector<unique_ptr<Expression>> bodyExpressions;
    bodyExpressions.push_back(std::move(_this->body));
    bodyExpressions.push_back(std::move(_this->modifier));

    auto whileLoop = Loop::create(std::move(_this->condition), Block::create(std::move(bodyExpressions)));
    return whileLoop->eval(env);
}

EvalResult Switch::eval(std::shared_ptr<Environment> env) const {
    // TODO: JIT-transpile to if-else chain

    for (const auto& branch : cases) {
        if (get<bool>(branch.first->eval(env))) {
            return branch.second->eval(env);
        }
    }

    return Null{};
}
