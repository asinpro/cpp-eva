#ifndef CPP_EVA_EXPRESSIONS_H
#define CPP_EVA_EXPRESSIONS_H

#include <vector>
#include <memory>
#include <string>
#include "eval_types.h"

class Environment;

struct Expression {
    [[nodiscard]] virtual EvalResult eval(std::shared_ptr<Environment> env) const {
        return Null{};
    }
};

class Block : public Expression {
public:
    explicit Block(std::vector<std::unique_ptr<Expression>> expressions)
            : expressions(std::move(expressions)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::vector<std::unique_ptr<Expression>> expressions;
};

class Condition : public Expression {
public:
    Condition(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> then, std::unique_ptr<Expression> otherwise)
            : condition(std::move(condition)), then(std::move(then)), otherwise(std::move(otherwise)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> then;
    std::unique_ptr<Expression> otherwise;
};

class Loop : public Expression {
public:
    Loop(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> body)
            : condition(std::move(condition)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> body;
};

struct Identifier : public Expression {
public:
    explicit Identifier(std::string name) : name(std::move(name)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
};

struct Literal : public Expression {
public:
    explicit Literal(EvalResult value) : value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override {
        return value;
    }

private:
    EvalResult value;
};

class VariableDeclaration : public Expression {
public:
    VariableDeclaration(std::string name, std::unique_ptr<Expression> value)
            : name(std::move(name)), value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::basic_string<char> name;
    std::unique_ptr<Expression> value;
};

class Assignment : public Expression {
public:
    Assignment(std::string name, std::unique_ptr<Expression> value)
            : name(std::move(name)), value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    std::unique_ptr<Expression> value;
};

class BinaryOperation : public Expression {
public:
    BinaryOperation(char type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
            : type(type), left(std::move(left)), right(std::move(right)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;
private:
    char type;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

class FunctionDefinition : public Expression {
public:
    FunctionDefinition(std::string name, std::vector<std::string> params, std::unique_ptr<Expression> body)
            : name(std::move(name)), params(std::move(params)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    std::vector<std::string> params;
    std::shared_ptr<Expression> body;
};

class FunctionCall : public Expression {
public:
    FunctionCall(std::string name, std::vector<std::unique_ptr<Expression>> args)
            : name(std::move(name)), args(std::move(args)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    std::vector<std::unique_ptr<Expression>> args;
};

#endif //CPP_EVA_EXPRESSIONS_H
