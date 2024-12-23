#ifndef CPP_EVA_EVA_H
#define CPP_EVA_EVA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <variant>
#include <regex>
#include "expressions.h"
#include "eval_types.h"
#include "environment.h"

using namespace std::string_literals;

/**
 * Global environment with predefined values.
 */
const auto globalEnv = std::make_shared<Environment>(EvalMap{
    {"VERSION", "0.1"s},
    {"null", Null{}},
    {"true", true},
    {"false", false},
    //        {"print", std::make_unique<Expression>())
    //        {"var", std::make_unique<Var>()},
    //        {"set", std::make_unique<Set>()},
    //        {"id", std::make_unique<Id>()},
    //        {"if", std::make_unique<If>()},
    //        {"loop", std::make_unique<Loop>()},
    //        {"+", std::make_unique<BinaryOperation>("+")},
    //        {"-", std::make_unique<BinaryOperation>("-")},
    //        {"*", std::make_unique<BinaryOperation>("*")},
    //        {"/", std::make_unique<BinaryOperation>("/")},
    //        {">", std::make_unique<BinaryOperation>(">")},
    //        {"<", std::make_unique<BinaryOperation}("<")},
    //        {"=", std::make_unique<BinaryOperation>("=")},
    //        {"block", std::make_unique<Block>()},
    //        {"condition", std::make_unique<Condition>()},
    //        {"literal", std::make_unique<Literal>()},
    //        {"identifier", std::make_unique<Identifier>()},
    //        {"variable_declaration", std::make_unique<VariableDeclaration>()},
    //        {"assignment", std::make_unique<Assignment>()},
    //        {"function", std::make_unique<FunctionDefinition>()},
    //        {"call", std::make_unique<Call>()},
    //        {"return", std::make_unique<Return>()},
    //        {"lambda", std::make_unique<Lambda>()},
    //        {"parameter", std::make_unique<Parameter>()},
    //        {"arguments", std::make_unique<Arguments>()},
    //        {"program", std::make_unique<Program>()}
});

/**
 * Class of Eva language interpreter.
 *
 * The eval method evaluates the expression and returns the result.
 */
class Eva
{
public:
    explicit Eva(std::shared_ptr<Environment> global = globalEnv)
        : global(global) {}

    /**
     * @brief Evaluate the expression in the global environment
     *
     * @param exp The expression to evaluate
     *
     * @return The result of the evaluation
     */
    int evalGlobal(Expression &exp)
    {
        return 0;
        //        return _evalBody(exp, global);
    }

    /**
     * @brief Evaluate the expression in the given environment
     *
     * @param exp The expression to evaluate
     * @param env The environment to evaluate the expression in
     *
     * @return The result of the evaluation
     */
    EvalResult eval(ExpressionPtr exp, std::shared_ptr<Environment> env = nullptr);

private:
    EvalResult _eval(ExpressionPtr exp, std::shared_ptr<Environment> env);

    int _evalBody(const std::vector<std::string> &exp, std::shared_ptr<Environment> env)
    {
        // Implement body evaluation
        return 0;
    }

    std::shared_ptr<Environment> global;
};

#endif // CPP_EVA_EVA_H
