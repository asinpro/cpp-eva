#ifndef CPP_EVA_EXPRESSIONS_H
#define CPP_EVA_EXPRESSIONS_H

#include <vector>
#include <memory>
#include <string>
#include "eval_types.h"

class Environment;

class Expression
{
public:
    static auto create()
    {
        return std::make_unique<Expression>();
    }

    [[nodiscard]] virtual EvalResult eval(std::shared_ptr<Environment> env) const
    {
        return Null{};
    }
};

using ExpressionPtr = std::unique_ptr<Expression>;

class Block : public Expression
{
public:
    static auto create(std::vector<ExpressionPtr> expressions)
    {
        return std::make_unique<Block>(std::move(expressions));
    }

    explicit Block(std::vector<ExpressionPtr> expressions)
        : expressions(std::move(expressions)) {}

    Block(Block &&other) noexcept;

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

    [[nodiscard]] EvalResult evalBlock(std::shared_ptr<Environment> env) const;

protected:
    std::vector<ExpressionPtr> expressions;
};

using BlockPtr = std::unique_ptr<Block>;

class Condition : public Expression
{
public:
    static auto create(ExpressionPtr condition, ExpressionPtr then, ExpressionPtr otherwise)
    {
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

class Loop : public Expression
{
public:
    static auto create(ExpressionPtr condition, ExpressionPtr body)
    {
        return std::make_unique<Loop>(std::move(condition), std::move(body));
    }

    Loop(ExpressionPtr condition, ExpressionPtr body)
        : condition(std::move(condition)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    ExpressionPtr condition;
    ExpressionPtr body;
};

struct Identifier : public Expression
{
public:
    static auto create(std::string name)
    {
        return std::make_unique<Identifier>(std::move(name));
    }

    explicit Identifier(std::string name) : name(std::move(name)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

    [[nodiscard]] std::string getName() const
    {
        return name;
    }

protected:
    std::string name;
};

using IdentifierPtr = std::unique_ptr<Identifier>;

struct Literal : public Expression
{
public:
    static auto create(EvalResult value)
    {
        return std::make_unique<Literal>(std::move(value));
    }

    explicit Literal(EvalResult value) : value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override
    {
        return value;
    }

private:
    EvalResult value;
};

class VariableDeclaration : public Expression
{
public:
    static auto create(std::string name, ExpressionPtr value)
    {
        return std::make_unique<VariableDeclaration>(std::move(name), std::move(value));
    }

    VariableDeclaration(std::string name, ExpressionPtr value)
        : name(std::move(name)), value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::basic_string<char> name;
    ExpressionPtr value;
};

using MemberAccessPtr = std::unique_ptr<class MemberAccess>;

class Assignment : public Expression
{
public:
    static auto create(std::string name, ExpressionPtr value)
    {
        return std::make_unique<Assignment>(std::move(name), std::move(value));
    }

    static auto create(MemberAccessPtr memberAccess, ExpressionPtr value)
    {
        return std::make_unique<Assignment>(std::move(memberAccess), std::move(value));
    }

    Assignment(std::string name, ExpressionPtr value)
        : name(std::move(name)), value(std::move(value)) {}

    Assignment(MemberAccessPtr memberAccess, ExpressionPtr value)
        : memberAccess(std::move(memberAccess)), value(std::move(value)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    ExpressionPtr value;
    MemberAccessPtr memberAccess;
};

enum BinaryOperationType
{
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

class BinaryOperation : public Expression
{
public:
    static auto create(BinaryOperationType type, ExpressionPtr left, ExpressionPtr right)
    {
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

class FunctionDeclaration : public Expression
{
public:
    static auto create(std::string name, std::vector<std::string> params, ExpressionPtr body)
    {
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

using FunctionDeclarationPtr = std::unique_ptr<FunctionDeclaration>;

class Lambda : public FunctionDeclaration
{
public:
    static auto create(std::vector<std::string> params, ExpressionPtr body)
    {
        return std::make_unique<Lambda>(std::move(params), std::move(body));
    }

    Lambda(std::vector<std::string> params, ExpressionPtr _body)
        : FunctionDeclaration("", std::move(params), std::move(_body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;
};

class AnonymousFunctionCall : public Expression
{
public:
    static auto create(FunctionDeclarationPtr function, std::vector<ExpressionPtr> args)
    {
        return std::make_unique<AnonymousFunctionCall>(std::move(function), std::move(args));
    }

    AnonymousFunctionCall(ExpressionPtr function, std::vector<ExpressionPtr> args)
        : function(std::move(function)), args(std::move(args)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

protected:
    [[nodiscard]] virtual FunctionDefinition resolveFunction(std::shared_ptr<Environment> env) const;

    [[nodiscard]] virtual FunctionDefinition resolveFunctionImpl(std::shared_ptr<Environment> env) const;

private:
    ExpressionPtr function;
    std::vector<ExpressionPtr> args;
};

class FunctionCall : public AnonymousFunctionCall
{
public:
    static auto create(std::string name, std::vector<ExpressionPtr> args)
    {
        return std::make_unique<FunctionCall>(std::move(name), std::move(args));
    }

    static auto create(IdentifierPtr identifier, std::vector<ExpressionPtr> args)
    {
        return std::make_unique<FunctionCall>(std::move(identifier->getName()), std::move(args));
    }

    FunctionCall(std::string name, std::vector<ExpressionPtr> args)
        : name(std::move(name)), AnonymousFunctionCall(nullptr, std::move(args)) {}

protected:
    [[nodiscard]] FunctionDefinition resolveFunction(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    std::vector<ExpressionPtr> args;
};

class ForLoop : public Expression
{
public:
    static auto create(ExpressionPtr init, ExpressionPtr condition, ExpressionPtr modifier, ExpressionPtr body)
    {
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

class Switch : public Expression
{
public:
    static auto create(std::vector<std::pair<ExpressionPtr, ExpressionPtr>> cases)
    {
        return std::make_unique<Switch>(std::move(cases));
    }

    explicit Switch(std::vector<std::pair<ExpressionPtr, ExpressionPtr>> cases)
        : cases(std::move(cases)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::vector<std::pair<ExpressionPtr, ExpressionPtr>> cases;
};

class Increment : public Expression
{
public:
    static auto create(IdentifierPtr identifier)
    {
        return std::make_unique<Increment>(std::move(identifier));
    }

    explicit Increment(IdentifierPtr _identifier) : identifier(std::move(_identifier)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    IdentifierPtr identifier;
};

class Decrement : public Expression
{
public:
    static auto create(IdentifierPtr identifier)
    {
        return std::make_unique<Decrement>(std::move(identifier));
    }

    explicit Decrement(IdentifierPtr _identifier) : identifier(std::move(_identifier)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    IdentifierPtr identifier;
};

class ClassDeclaration : public Block
{
public:
    static auto create(std::string name, IdentifierPtr parent, BlockPtr body)
    {
        return std::make_unique<ClassDeclaration>(std::move(name), std::move(parent), std::move(body));
    }

    ClassDeclaration(std::string name, IdentifierPtr parent, BlockPtr body)
        : Block(std::move(*body.release())), name(std::move(name)), parent(std::move(parent)), body(std::move(body)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    IdentifierPtr parent;
    ExpressionPtr body;
};

class NewInstance : public Expression
{
public:
    static auto create(std::string name, std::vector<ExpressionPtr> args)
    {
        return std::make_unique<NewInstance>(std::move(name), std::move(args));
    }

    NewInstance(std::string name, std::vector<ExpressionPtr> args)
        : name(std::move(name)), args(std::move(args)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

private:
    std::string name;
    std::vector<ExpressionPtr> args;
};

class MemberAccess : public Identifier
{
public:
    static auto create(std::string instance, std::string member)
    {
        return std::make_unique<MemberAccess>(std::move(instance), std::move(member));
    }

    MemberAccess(std::string instance, std::string member)
        : Identifier(std::move(member)), instance(std::move(instance)) {}

    [[nodiscard]] EvalResult eval(std::shared_ptr<Environment> env) const override;

    std::string getInstance() const
    {
        return instance;
    }

    std::string getMember() const
    {
        return getName();
    }

private:
    std::string instance;
};

class MemberFunctionCall : public AnonymousFunctionCall
{
public:
    static auto create(MemberAccessPtr memberFunction, std::vector<ExpressionPtr> args)
    {
        return std::make_unique<MemberFunctionCall>(std::move(memberFunction), std::move(args));
    }

    MemberFunctionCall(MemberAccessPtr memberFunction, std::vector<ExpressionPtr> args)
        : AnonymousFunctionCall(std::move(memberFunction), std::move(args)) {}

protected:
    [[nodiscard]] FunctionDefinition resolveFunction(std::shared_ptr<Environment> env) const override;
};

#endif // CPP_EVA_EXPRESSIONS_H
