#include "expressions.h"

#include <string>
#include <variant>
#include "eval_types.h"
#include "environment.h"

using namespace std;

EvalResult VariableDeclaration::eval(std::shared_ptr<Environment> env) const
{
    const EvalResult &val = value->eval(env);
    env->define(name, val);
    return val;
}

EvalResult Assignment::eval(std::shared_ptr<Environment> env) const
{
    if (memberAccess)
    {
        auto instanceDefinition = get<InstanceDefinition>(env->lookup(memberAccess->getInstance()));
        auto memberName = memberAccess->getMember();

        const EvalResult &val = value->eval(env);
        instanceDefinition.env->define(memberName, val);
        return val;
    }

    return env->assign(name, value->eval(env));
}

EvalResult Identifier::eval(std::shared_ptr<Environment> env) const
{
    return env->lookup(name);
}

EvalResult BinaryOperation::eval(std::shared_ptr<Environment> env) const
{
    const int lhs = get<int>(left->eval(env));
    const int rhs = get<int>(right->eval(env));

    switch (type)
    {
    case BinaryOperationType::ADDITION:
        return lhs + rhs;
    case BinaryOperationType::SUBTRACTION:
        return lhs - rhs;
    case BinaryOperationType::MULTIPLICATION:
        return lhs * rhs;
    case BinaryOperationType::DIVISION:
        return lhs / rhs;
    case BinaryOperationType::MOD:
        return lhs % rhs;
    case BinaryOperationType::GREATER:
        return lhs > rhs;
    case BinaryOperationType::LESS:
        return lhs < rhs;
    case BinaryOperationType::EQUAL:
        return lhs == rhs;
    case BinaryOperationType::NOT_EQUAL:
        return lhs != rhs;
    case BinaryOperationType::GREATER_OR_EQUAL:
        return lhs >= rhs;
    case BinaryOperationType::LESS_OR_EQUAL:
        return lhs <= rhs;
    default:
        throw runtime_error("Unknown operation: " + string(1, type));
    }
}

EvalResult Block::eval(std::shared_ptr<Environment> env) const
{
    EvalMap vars;
    auto blockEnv = make_shared<Environment>(vars, env);
    return evalBlock(blockEnv);
}

Block::Block(Block &&other) noexcept
{
    swap(expressions, other.expressions);
}

EvalResult Block::evalBlock(std::shared_ptr<Environment> env) const
{
    EvalResult result;
    for (const auto &exp : expressions)
    {
        result = exp->eval(env);
    }
    return result;
}

EvalResult Condition::eval(std::shared_ptr<Environment> env) const
{
    if (get<bool>(condition->eval(env)))
    {
        return then->eval(env);
    }
    else
    {
        return otherwise->eval(env);
    }
}

EvalResult Loop::eval(std::shared_ptr<Environment> env) const
{
    EvalResult result;
    while (get<bool>(condition->eval(env)))
    {
        result = body->eval(env);
    }
    return result;
}

EvalResult FunctionDeclaration::eval(std::shared_ptr<Environment> env) const
{
    // JIT-transpile to variable declaration with lambda

    auto _this = const_cast<FunctionDeclaration *>(this);
    auto lambda = Lambda::create(params, std::move(_this->body));

    auto value = lambda->eval(env);
    env->define(name, value);
    return value;
}

FunctionDefinition FunctionCall::resolveFunction(std::shared_ptr<Environment> env) const
{
    return get<FunctionDefinition>(env->lookup(name));
}

EvalResult Lambda::eval(std::shared_ptr<Environment> env) const
{
    auto _this = const_cast<Lambda *>(this);
    return FunctionDefinition{name, params, std::move(_this->body), env};
}

EvalResult AnonymousFunctionCall::eval(std::shared_ptr<Environment> env) const
{
    const auto fun = resolveFunction(env);
    auto funEnv = make_shared<Environment>(EvalMap{}, fun.env);

    for (size_t i = 0; i < fun.params.size(); ++i)
    {
        funEnv->define(fun.params[i], args[i]->eval(env));
    }

    return fun.body->eval(funEnv);
}

FunctionDefinition AnonymousFunctionCall::resolveFunction(std::shared_ptr<Environment> env) const
{
    return resolveFunctionImpl(nullptr);
}

FunctionDefinition AnonymousFunctionCall::resolveFunctionImpl(std::shared_ptr<Environment> env) const
{
    return get<FunctionDefinition>(function->eval(env));
}

EvalResult ForLoop::eval(std::shared_ptr<Environment> env) const
{
    // JIT-transpile to while loop

    auto _ = init->eval(env);
    auto _this = const_cast<ForLoop *>(this);

    vector<unique_ptr<Expression>> bodyExpressions;
    bodyExpressions.push_back(std::move(_this->body));
    bodyExpressions.push_back(std::move(_this->modifier));

    auto whileLoop = Loop::create(std::move(_this->condition), Block::create(std::move(bodyExpressions)));
    return whileLoop->eval(env);
}

EvalResult Switch::eval(std::shared_ptr<Environment> env) const
{
    if (cases.empty())
    {
        return Null{};
    }

    auto _this = const_cast<Switch *>(this);

    unique_ptr<Condition> condition = Condition::create(
        std::move(_this->cases.back().first),
        std::move(_this->cases.back().second),
        nullptr);

    for (auto i = cases.size(); i-- > 1;)
    {
        condition = Condition::create(
            std::move(_this->cases[i - 1].first),
            std::move(_this->cases[i - 1].second),
            std::move(condition));
    }

    return condition->eval(env);
}

EvalResult Increment::eval(std::shared_ptr<Environment> env) const
{
    // JIT-transpile to addition with assignment

    auto assignment = Assignment::create(identifier->getName(), BinaryOperation::create(
                                                                    BinaryOperationType::ADDITION,
                                                                    Literal::create(identifier->eval(env)),
                                                                    Literal::create(1)));

    return assignment->eval(env);
}

EvalResult Decrement::eval(std::shared_ptr<Environment> env) const
{
    // JIT-transpile to subtraction with assignment

    auto assignment = Assignment::create(identifier->getName(), BinaryOperation::create(
                                                                    BinaryOperationType::SUBTRACTION,
                                                                    Literal::create(identifier->eval(env)),
                                                                    Literal::create(1)));

    return assignment->eval(env);
}

EvalResult ClassDeclaration::eval(std::shared_ptr<Environment> env) const
{
    auto parentEnv = env;
    const EvalResult &result = parent->eval(env);
    if (auto classDefinition = get_if<ClassDefinition>(&result))
    {
        parentEnv = classDefinition->env;
    }

    auto classEnv = make_shared<Environment>(EvalMap{}, parentEnv);
    void(evalBlock(classEnv));
    env->define(name, ClassDefinition{name, classEnv});

    return Null{};
}

EvalResult NewInstance::eval(std::shared_ptr<Environment> env) const
{
    auto classDefinition = get<ClassDefinition>(env->lookup(name));
    auto instanceEnv = make_shared<Environment>(EvalMap{}, classDefinition.env);

    auto constructorDefinition = get<FunctionDefinition>(classDefinition.env->lookup("constructor"));
    auto constructorEnv = make_shared<Environment>(EvalMap{}, constructorDefinition.env);

    const InstanceDefinition &instanceDefinition = InstanceDefinition{instanceEnv};
    constructorEnv->define("self", instanceDefinition);

    for (size_t i = 1; i < constructorDefinition.params.size(); ++i)
    {
        constructorEnv->define(constructorDefinition.params[i], args[i - 1]->eval(env));
    }

    void(constructorDefinition.body->eval(constructorEnv));

    return instanceDefinition;
}

EvalResult MemberAccess::eval(std::shared_ptr<Environment> env) const
{
    auto instanceDefinition = get<InstanceDefinition>(env->lookup(instance));
    return instanceDefinition.env->lookup(getMember());
}

FunctionDefinition MemberFunctionCall::resolveFunction(std::shared_ptr<Environment> env) const
{
    return resolveFunctionImpl(env);
}
