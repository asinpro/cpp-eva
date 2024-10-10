#ifndef CPP_EVA_EXPRESSIONS_H
#define CPP_EVA_EXPRESSIONS_H

#include <vector>
#include <memory>
#include <string>
#include "eval_types.h"

class Environment;

class Expression {
public:
    static auto create() {
        return std::make_unique<Expression>();
    }

    [[nodiscard]] virtual EvalResult eval(std::shared_ptr<Environment> env) const {
        return Null{};
    }
};

using ExpressionPtr = std::unique_ptr<Expression>;

class Block : public Expression {
public:
    static auto create(std::vector<ExpressionPtr> expressions) {
        return std::make_unique<Block>(std::move(expressions));
    }

    explicit Block(std::vector<ExpressionPtr> expressions)
            : expressions(std::move(expressions)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::vector<ExpressionPtr> expressions;
};

class Condition : public Expression {
public:
    static auto create(ExpressionPtr condition, ExpressionPtr then, ExpressionPtr otherwise) {
        return std::make_unique<Condition>(std::move(condition), std::move(then), std::move(otherwise));
    }

    Condition(ExpressionPtr condition, ExpressionPtr then, ExpressionPtr otherwise)
            : condition(std::move(condition)), then(std::move(then)), otherwise(std::move(otherwise)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    ExpressionPtr condition;
    ExpressionPtr then;
    ExpressionPtr otherwise;
};

class Loop : public Expression {
public:
    static auto create(ExpressionPtr condition, ExpressionPtr body) {
        return std::make_unique<Loop>(std::move(condition), std::move(body));
    }

    Loop(ExpressionPtr condition, ExpressionPtr body)
            : condition(std::move(condition)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    ExpressionPtr condition;
    ExpressionPtr body;
};

struct Identifier : public Expression {
public:
    static auto create(std::string name) {
        return std::make_unique<Identifier>(std::move(name));
    }

    explicit Identifier(std::string name) : name(std::move(name)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
};

struct Literal : public Expression {
public:
    static auto create(EvalResult value) {
        return std::make_unique<Literal>(std::move(value));
    }

    explicit Literal(EvalResult value) : value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override {
        return value;
    }

private:
    EvalResult value;
};

class VariableDeclaration : public Expression {
public:
    static auto create(std::string name, ExpressionPtr value) {
        return std::make_unique<VariableDeclaration>(std::move(name), std::move(value));
    }

    VariableDeclaration(std::string name, ExpressionPtr value)
            : name(std::move(name)), value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::basic_string<char> name;
    ExpressionPtr value;
};

class Assignment : public Expression {
public:
    static auto create(std::string name, ExpressionPtr value) {
        return std::make_unique<Assignment>(std::move(name), std::move(value));
    }

    Assignment(std::string name, ExpressionPtr value)
            : name(std::move(name)), value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    ExpressionPtr value;
};

enum BinaryOperationType {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MOD,
    GREATER,
    LESS,
    EQUAL,
    NOT_EQUAL,
    GREATER_OR_EQUAL,
    LESS_OR_EQUAL
};

class BinaryOperation : public Expression {
public:
    static auto create(BinaryOperationType type, ExpressionPtr left, ExpressionPtr right) {
        return std::make_unique<BinaryOperation>(type, std::move(left), std::move(right));
    }

    BinaryOperation(BinaryOperationType type, ExpressionPtr left, ExpressionPtr right)
            : type(type), left(std::move(left)), right(std::move(right)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;
private:
    BinaryOperationType type;
    ExpressionPtr left;
    ExpressionPtr right;
};

class FunctionDeclaration : public Expression {
public:
    static auto create(std::string name, std::vector<std::string> params, ExpressionPtr body) {
        return std::make_unique<FunctionDeclaration>(std::move(name), std::move(params), std::move(body));
    }

    FunctionDeclaration(std::string name, std::vector<std::string> params, ExpressionPtr body)
            : name(std::move(name)), params(std::move(params)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

protected:
    std::string name;
    std::vector<std::string> params;
    ExpressionPtr body;
};

class AnonymousFunctionCall : public Expression {
public:
    static auto create(ExpressionPtr function, std::vector<ExpressionPtr> args) {
        return std::make_unique<AnonymousFunctionCall>(std::move(function), std::move(args));
    }

    AnonymousFunctionCall(ExpressionPtr function, std::vector<ExpressionPtr> args)
            : function(std::move(function)), args(std::move(args)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

protected:
    [[nodiscard]] virtual Function resolveFunction(std::shared_ptr<Environment> env) const;

private:
    ExpressionPtr function;
    std::vector<ExpressionPtr> args;
};

class FunctionCall : public AnonymousFunctionCall {
public:
    static auto create(std::string name, std::vector<ExpressionPtr> args) {
        return std::make_unique<FunctionCall>(std::move(name), std::move(args));
    }

    FunctionCall(std::string name, std::vector<ExpressionPtr> _args)
            : name(std::move(name)), AnonymousFunctionCall(nullptr, std::move(_args)) {}

protected:
    [[nodiscard]] Function resolveFunction(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    std::vector<ExpressionPtr> args;
};

class Lambda : public FunctionDeclaration {
public:
    static auto create(std::vector<std::string> params, ExpressionPtr body) {
        return std::make_unique<Lambda>(std::move(params), std::move(body));
    }

    Lambda(std::vector<std::string> _params, ExpressionPtr _body)
            : FunctionDeclaration("", std::move(_params), std::move(_body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;
};

class ForLoop : public Expression {
public:
    static auto create(ExpressionPtr init, ExpressionPtr condition, ExpressionPtr modifier, ExpressionPtr body) {
        return std::make_unique<ForLoop>(std::move(init), std::move(condition), std::move(modifier), std::move(body));
    }

    ForLoop(ExpressionPtr init, ExpressionPtr condition, ExpressionPtr modifier, ExpressionPtr body)
            : init(std::move(init)), condition(std::move(condition)), modifier(std::move(modifier)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    ExpressionPtr init;
    ExpressionPtr condition;
    ExpressionPtr modifier;
    ExpressionPtr body;
};

class Switch : public Expression {
public:
    static auto create(std::vector<std::pair<ExpressionPtr, ExpressionPtr>> cases) {
        return std::make_unique<Switch>(std::move(cases));
    }

    explicit Switch(std::vector<std::pair<ExpressionPtr, ExpressionPtr>> cases)
            : cases(std::move(cases)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::vector<std::pair<ExpressionPtr, ExpressionPtr>> cases;
};

#endif //CPP_EVA_EXPRESSIONS_H
