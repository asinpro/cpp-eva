#ifndef CPP_EVA_EVAL_TYPES_H
#define CPP_EVA_EVAL_TYPES_H

#include <utility>
#include <variant>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class Environment;

struct Null {
};

using EvalResult = std::variant<int, std::string, bool, Null>;
using EvalMap = std::unordered_map<std::string, EvalResult>;

inline bool operator==(const Null&, const Null&) {
    return true;
}

struct Expression {
    [[nodiscard]] virtual EvalResult eval(std::shared_ptr<Environment> env) const {
        return Null{};
    }
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

#endif //CPP_EVA_EVAL_TYPES_H
