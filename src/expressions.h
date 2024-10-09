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

class Block : public Expression {
public:
    static auto create(std::vector<std::unique_ptr<Expression>> expressions) {
        return std::make_unique<Block>(std::move(expressions));
    }

    explicit Block(std::vector<std::unique_ptr<Expression>> expressions)
            : expressions(std::move(expressions)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::vector<std::unique_ptr<Expression>> expressions;
};

class Condition : public Expression {
public:
    static auto create(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> then, std::unique_ptr<Expression> otherwise) {
        return std::make_unique<Condition>(std::move(condition), std::move(then), std::move(otherwise));
    }

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
    static auto create(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> body) {
        return std::make_unique<Loop>(std::move(condition), std::move(body));
    }

    Loop(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> body)
            : condition(std::move(condition)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> body;
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
    static auto create(std::string name, std::unique_ptr<Expression> value) {
        return std::make_unique<VariableDeclaration>(std::move(name), std::move(value));
    }

    VariableDeclaration(std::string name, std::unique_ptr<Expression> value)
            : name(std::move(name)), value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::basic_string<char> name;
    std::unique_ptr<Expression> value;
};

class Assignment : public Expression {
public:
    static auto create(std::string name, std::unique_ptr<Expression> value) {
        return std::make_unique<Assignment>(std::move(name), std::move(value));
    }

    Assignment(std::string name, std::unique_ptr<Expression> value)
            : name(std::move(name)), value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    std::unique_ptr<Expression> value;
};

class BinaryOperation : public Expression {
public:
    static auto create(char type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) {
        return std::make_unique<BinaryOperation>(type, std::move(left), std::move(right));
    }

    BinaryOperation(char type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
            : type(type), left(std::move(left)), right(std::move(right)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;
private:
    char type;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

class FunctionDeclaration : public Expression {
public:
    static auto create(std::string name, std::vector<std::string> params, std::unique_ptr<Expression> body) {
        return std::make_unique<FunctionDeclaration>(std::move(name), std::move(params), std::move(body));
    }

    FunctionDeclaration(std::string name, std::vector<std::string> params, std::unique_ptr<Expression> body)
            : name(std::move(name)), params(std::move(params)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

protected:
    std::string name;
    std::vector<std::string> params;
    std::unique_ptr<Expression> body;
};

class AnonymousFunctionCall : public Expression {
public:
    static auto create(std::unique_ptr<Expression> function, std::vector<std::unique_ptr<Expression>> args) {
        return std::make_unique<AnonymousFunctionCall>(std::move(function), std::move(args));
    }

    AnonymousFunctionCall(std::unique_ptr<Expression> function, std::vector<std::unique_ptr<Expression>> args)
            : function(std::move(function)), args(std::move(args)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

protected:
    [[nodiscard]] virtual Function resolveFunction(std::shared_ptr<Environment> env) const;

private:
    std::unique_ptr<Expression> function;
    std::vector<std::unique_ptr<Expression>> args;
};

class FunctionCall : public AnonymousFunctionCall {
public:
    static auto create(std::string name, std::vector<std::unique_ptr<Expression>> args) {
        return std::make_unique<FunctionCall>(std::move(name), std::move(args));
    }

    FunctionCall(std::string name, std::vector<std::unique_ptr<Expression>> _args)
            : name(std::move(name)), AnonymousFunctionCall(nullptr, std::move(_args)) {}

protected:
    [[nodiscard]] Function resolveFunction(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    std::vector<std::unique_ptr<Expression>> args;
};

class Lambda : public FunctionDeclaration {
public:
    static auto create(std::vector<std::string> params, std::unique_ptr<Expression> body) {
        return std::make_unique<Lambda>(std::move(params), std::move(body));
    }

    Lambda(std::vector<std::string> _params, std::unique_ptr<Expression> _body)
            : FunctionDeclaration("", std::move(_params), std::move(_body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;
};

class ForLoop : public Expression {
public:
    static auto create(std::unique_ptr<Expression> init, std::unique_ptr<Expression> condition, std::unique_ptr<Expression> modifier, std::unique_ptr<Expression> body) {
        return std::make_unique<ForLoop>(std::move(init), std::move(condition), std::move(modifier), std::move(body));
    }

    ForLoop(std::unique_ptr<Expression> init, std::unique_ptr<Expression> condition, std::unique_ptr<Expression> modifier, std::unique_ptr<Expression> body)
            : init(std::move(init)), condition(std::move(condition)), modifier(std::move(modifier)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::unique_ptr<Expression> init;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Expression> modifier;
    std::unique_ptr<Expression> body;
};

class Switch : public Expression {
public:
    static auto create(std::vector<std::pair<std::unique_ptr<Expression>, std::unique_ptr<Expression>>> cases) {
        return std::make_unique<Switch>(std::move(cases));
    }

    explicit Switch(std::vector<std::pair<std::unique_ptr<Expression>, std::unique_ptr<Expression>>> cases)
            : cases(std::move(cases)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::vector<std::pair<std::unique_ptr<Expression>, std::unique_ptr<Expression>>> cases;
};

#endif //CPP_EVA_EXPRESSIONS_H
