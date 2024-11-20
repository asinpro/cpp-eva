#ifndef CPP_EVA_EXPRESSION_HELPERS_H
#define CPP_EVA_EXPRESSION_HELPERS_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "../expressions.h"

#define TRUE id("true")
#define FALSE id("false")
#define NONE id("null")
#define none NONE

#define ID_NAME(name) #name

/**
 * @brief Print expression
 *
 * @param args Args&&...
 * @return ExpressionPtr
 *
 * @code
 * print("Hello, ", "world!");
 * @endcode
 */
template <typename... Args>
inline auto print(Args &&...args)
{
    (std::cout << ... << args) << std::endl;
    return Expression::create();
}

/**
 * @brief Create new literal expression
 *
 * @param value EvalResult
 * @return LiteralPtr
 *
 * @code
 * lit(value);
 * @endcode
 */
inline auto lit(EvalResult value)
{
    return Literal::create(std::move(value));
}

inline auto wrap(ExpressionPtr value)
{
    return std::move(value);
}

inline auto wrap(EvalResult value)
{
    return lit(std::move(value));
}

/**
 * @brief Create new block expression
 *
 * @param args Args&&...
 * @return BlockPtr
 *
 * @code
 * beg(lit(1), lit(2), lit(3));
 * @endcode
 */
template <typename... Args>
inline auto beg(Args &&...args)
{
    std::vector<ExpressionPtr> expressions;
    (expressions.push_back(std::forward<Args>(args)), ...);
    return Block::create(std::move(expressions));
}

/**
 * @brief Create new condition expression
 *
 * @param condition ExpressionPtr
 * @param then ExpressionPtr
 *
 * @code
 * iff(eq(id("a"), id("b")), lit(1), lit(2));
 * @endcode
 */
inline auto iff(ExpressionPtr condition, ExpressionPtr then, ExpressionPtr otherwise)
{
    return Condition::create(std::move(condition), std::move(then), std::move(otherwise));
}

/**
 * @brief Create new while loop expression
 *
 * @param condition ExpressionPtr
 * @param body ExpressionPtr
 *
 * @code
 * loop(eq(id("a"), id("b")), lit(1));
 * @endcode
 */
inline ExpressionPtr loop(ExpressionPtr condition, ExpressionPtr body)
{
    return Loop::create(std::move(condition), std::move(body));
}

/**
 * @brief Create new for loop expression
 *
 * @param init ExpressionPtr
 * @param condition ExpressionPtr
 * @param modifier ExpressionPtr
 * @param body ExpressionPtr
 * @return ForLoopPtr
 *
 * @code
 * floop(lit(0), lt(id("i"), lit(10)), inc(id("i")), lit(1));
 * @endcode
 */
inline auto floop(ExpressionPtr init, ExpressionPtr condition, ExpressionPtr modifier, ExpressionPtr body)
{
    return ForLoop::create(std::move(init), std::move(condition), std::move(modifier), std::move(body));
}

/**
 * @brief Create new identifier
 *
 * @param name std::string
 * @return IdentifierPtr
 *
 * @code
 * id("name");
 * @endcode
 */
inline auto id(std::string name)
{
    return Identifier::create(std::move(name));
}

/**
 * @brief Create new variable declaration
 *
 * @param name std::string
 * @param value ExpressionPtr
 * @return VariableDeclarationPtr
 *
 * @code
 * var("name", value);
 * @endcode
 */
inline auto var(std::string name, ExpressionPtr value)
{
    return VariableDeclaration::create(std::move(name), std::move(value));
}

/**
 * @brief Create new variable declaration
 *
 * @param name std::string
 * @param value EvalResult
 * @return VariableDeclarationPtr
 *
 * @code
 * var("name", value);
 * @endcode
 */
inline auto var(std::string name, EvalResult value)
{
    return var(std::move(name), lit(std::move(value)));
}

/**
 * @brief Create new assignment expression
 *
 * @param name std::string
 * @param value ExpressionPtr
 * @return AssignmentPtr
 *
 * @code
 * set("name", value);
 * @endcode
 */
inline auto set(std::string name, ExpressionPtr value)
{
    return Assignment::create(std::move(name), std::move(value));
}

/**
 * @brief Create new assignment expression
 *
 * @param name std::string
 * @param value EvalResult
 * @return AssignmentPtr
 *
 * @code
 * set("name", value);
 * @endcode
 */
inline auto set(std::string name, EvalResult value)
{
    return set(std::move(name), lit(std::move(value)));
}

/**
 * @brief Create new assignment expression
 *
 * @param name std::string
 * @param value EvalResult
 * @return AssignmentPtr
 *
 * @code
 * set("name", value);
 * @endcode
 */
inline auto set(MemberAccessPtr memberAccess, ExpressionPtr value)
{
    return Assignment::create(std::move(memberAccess), std::move(value));
}

/**
 * @brief Create new grater than expression
 *
 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * gt(id("a"), id("b"));
 * @endcode
 */
inline auto gt(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return BinaryOperation::create(BinaryOperationType::GREATER, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new grater than expression
 *
 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * gt(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto gt(T &&lhs, U &&rhs)
{
    return gt(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new grater than or equal expression
 *
 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * gte(id("a"), id("b"));
 * @endcode
 */
inline auto gte(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return BinaryOperation::create(BinaryOperationType::GREATER_OR_EQUAL, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new grater than or equal expression
 *
 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * gte(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto gte(T &&lhs, U &&rhs)
{
    return gte(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new less than expression
 *
 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * lt(id("a"), id("b"));
 * @endcode
 */
inline auto lt(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return std::make_unique<BinaryOperation>(BinaryOperationType::LESS, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new less than expression
 *
 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * lt(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto lt(T &&lhs, U &&rhs)
{
    return lt(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new less than or equal expression
 *
 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * lte(id("a"), id("b"));
 * @endcode
 */
inline auto lte(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return BinaryOperation::create(BinaryOperationType::LESS_OR_EQUAL, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new less than or equal expression
 *
 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * lte(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto lte(T &&lhs, U &&rhs)
{
    return lte(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new equal expression
 *
 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * eq(id("a"), id("b"));
 * @endcode
 */
inline auto eq(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return std::make_unique<BinaryOperation>(BinaryOperationType::EQUAL, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new equal expression
 *
 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * eq(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto eq(T &&lhs, U &&rhs)
{
    return eq(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new not equal expression
 *
 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * neq(id("a"), id("b"));
 * @endcode
 */
inline auto neq(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return std::make_unique<BinaryOperation>(BinaryOperationType::NOT_EQUAL, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new not equal expression
 *
 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * neq(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto neq(T &&lhs, U &&rhs)
{
    return neq(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new addition expression

 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * add(id("a"), id("b"));
 * @endcode
 */
inline auto add(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return BinaryOperation::create(BinaryOperationType::ADDITION, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new addition expression

 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * add(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto add(T &&lhs, U &&rhs)
{
    return add(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new subtraction expression

 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * sub(id("a"), id("b"));
 * @endcode
 */
inline auto sub(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return BinaryOperation::create(BinaryOperationType::SUBTRACTION, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new subtraction expression

 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * sub(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto sub(T &&lhs, U &&rhs)
{
    return sub(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new multiplication expression

 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * mul(id("a"), id("b"));
 * @endcode
 */
inline auto mul(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return BinaryOperation::create(BinaryOperationType::MULTIPLICATION, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new multiplication expression

 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * mul(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto mul(T &&lhs, U &&rhs)
{
    return mul(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new division expression

 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * divv(id("a"), id("b"));
 * @endcode
 */
inline auto divv(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return BinaryOperation::create(BinaryOperationType::DIVISION, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new division expression

 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * divv(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto divv(T &&lhs, U &&rhs)
{
    return divv(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new modulo expression

 * @param lhs ExpressionPtr
 * @param rhs ExpressionPtr
 * @return BinaryOperationPtr
 *
 * @code
 * mod(id("a"), id("b"));
 * @endcode
 */
inline auto mod(ExpressionPtr lhs, ExpressionPtr rhs)
{
    return BinaryOperation::create(BinaryOperationType::MOD, std::move(lhs), std::move(rhs));
}

/**
 * @brief Create new modulo expression

 * @param lhs T&&
 * @param rhs U&&
 * @return BinaryOperationPtr
 *
 * @code
 * mod(id("a"), id("b"));
 * @endcode
 */
template <typename T, typename U>
inline auto mod(T &&lhs, U &&rhs)
{
    return mod(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

/**
 * @brief Create new increment expression

 * @param value IdentifierPtr
 * @return IncrementPtr
 *
 * @code
 * inc(id("a"));
 * @endcode
 */
inline auto inc(IdentifierPtr value)
{
    return Increment::create(std::move(value));
}

/**
 * @brief Create new decrement expression
 *
 * @param value IdentifierPtr
 * @return DecrementPtr
 *
 * @code
 * dec(id("a"));
 * @endcode
 */
inline auto dec(IdentifierPtr value)
{
    return Decrement::create(std::move(value));
}

/**
 * @brief Create new function declaration
 *
 * @param name std::string
 * @param args std::vector<std::string>
 * @param body ExpressionPtr
 * @return FunctionDeclarationPtr
 *
 * @code
 * def("functionName", args("a", "b"), lit(1));
 * @endcode
 */
inline auto def(std::string name, std::vector<std::string> args, ExpressionPtr body)
{
    return FunctionDeclaration::create(std::move(name), std::move(args), std::move(body));
}

/**
 * @brief Create new function declaration
 *
 * @param name std::string
 * @param args std::vector<std::string>
 * @param body EvalResult
 * @return FunctionDeclarationPtr
 *
 * @code
 * def("functionName", args("a", "b"), value);
 * @endcode
 */
inline auto def(std::string name, std::vector<std::string> args, EvalResult body)
{
    return def(std::move(name), std::move(args), lit(std::move(body)));
}

/**
 * @brief Create new lambda expression
 *
 * @param args std::vector<std::string>
 * @param body ExpressionPtr
 * @return LambdaPtr
 *
 * @code
 * lambda(args("a", "b"), add(id("a"), id("b")));
 * @endcode
 */
inline auto lambda(std::vector<std::string> args, ExpressionPtr body)
{
    return Lambda::create(std::move(args), std::move(body));
}

/**
 * @brief Create args vector for function declaration
 *
 * @param args Args&&...
 * @return std::vector<std::string>
 *
 * @code
 * def("functionName", args("a", "b"), lit(1));
 * @endcode
 */
template <typename... Args>
inline auto args(Args &&...args)
{
    std::vector<std::string> names;
    (names.push_back(std::forward<Args>(args)), ...);
    return names;
}

/**
 * @brief Create args vector for function call
 *
 * @param args Args&&...
 * @return std::vector<ExpressionPtr>
 *
 * @code
 * call("functionName", vars(arg1, arg2, arg3));
 * @endcode
 */
template <typename... Args>
inline auto vars(Args &&...args)
{
    std::vector<ExpressionPtr> expressions;
    (expressions.push_back(wrap(std::forward<Args>(args))), ...);
    return expressions;
}

/**
 * @brief Call function
 *
 * @param name std::string
 * @param args std::vector<ExpressionPtr>
 * @return FunctionCallPtr
 *
 * @code
 * call("functionName", vars(arg1, arg2, arg3));
 * @endcode
 */
inline auto call(std::string name, std::vector<ExpressionPtr> args)
{
    return FunctionCall::create(std::move(name), std::move(args));
}

/**
 * @brief Call function
 *
 * @param name std::string
 * @param args Args&&...
 * @return FunctionCallPtr
 *
 * @code
 * call("functionName", arg1, arg2, arg3);
 * @endcode
 */
template <typename... Args>
inline auto call(std::string name, Args &&...args)
{
    return call(std::move(name), vars(std::forward<Args>(args)...));
}

/**
 * @brief Call lambda inplace - Immediately Invoked Lambda Expression (IILE)
 *
 * @param exp FunctionDeclarationPtr
 * @param args std::vector<ExpressionPtr>
 * @return AnonymousFunctionCallPtr
 *
 * @code
 * iile(lambda(args("a", "b"), add(id(a), id(b))), vars(1, 2));
 * @endcode
 */
inline auto iile(FunctionDeclarationPtr exp, std::vector<ExpressionPtr> args)
{
    return AnonymousFunctionCall::create(std::move(exp), std::move(args));
}

/**
 * @brief Call lambda inplace - Immediately Invoked Lambda Expression (IILE)
 *
 * @param exp FunctionDeclarationPtr
 * @param args Args&&...
 * @return AnonymousFunctionCallPtr
 *
 * @code
 * iile(lambda(args(a, b), add(id(a), id(b))), 1, 2);
 * @endcode
 */
template <typename... Args>
inline auto iile(FunctionDeclarationPtr exp, Args &&...args)
{
    return iile(std::move(exp), vars(std::forward<Args>(args)...));
}

/**
 * @brief Create new switch statement
 *
 * @param condition ExpressionPtr
 * @param body ExpressionPtr
 * @return std::pair<ExpressionPtr, ExpressionPtr>
 *
 * @code
 * when(eq(id("a"), id("b")), 1);
 * when(eq(id("a"), 1)), 1);
 * @endcode
 */
template <typename T>
inline std::pair<ExpressionPtr, ExpressionPtr> when(ExpressionPtr condition, T &&body)
{
    return std::make_pair(std::move(condition), wrap(std::forward<T>(body)));
}

/**
 * @brief Create new switch statement with default case
 *
 * @param value ExpressionPtr
 * @return std::pair<ExpressionPtr, ExpressionPtr>
 *
 * @code
 * any(3);
 * @endcode
 */
template <typename T>
inline std::pair<ExpressionPtr, ExpressionPtr> any(T &&value)
{
    return std::make_pair(TRUE, wrap(std::forward<T>(value)));
}

/**
 * @brief Create new switch statement
 *
 * @param args std::pair<ExpressionPtr, ExpressionPtr>
 * @return SwitchPtr
 *
 * @code
 * select(
 *    when(eq(id("a"), id("b")), 1),
 *    when(eq(id("a"), id("c")), 2),
 *    any(3)
 * );
 * @endcode
 * @endcode
 */
template <typename... Args>
inline auto select(Args &&...args)
{
    auto cases = std::vector<std::pair<ExpressionPtr, ExpressionPtr>>();
    (cases.push_back(std::forward<Args>(args)), ...);
    return Switch::create(std::move(cases));
}

/**
 * @brief Create new class declaration
 *
 * @param name std::string
 * @param parent IdentifierPtr
 * @param body BlockPtr
 *
 * @code
 * cls("ClassName", parent, body);
 * @endcode
 */
inline auto cls(std::string name, IdentifierPtr parent, BlockPtr body)
{
    return ClassDeclaration::create(std::move(name), std::move(parent), std::move(body));
}

/**
 * @brief Create new instance of class
 *
 * @param name std::string
 * @param args std::vector<ExpressionPtr>
 * @return NewInstancePtr
 *
 * @code
 * newi("ClassName", vars(arg1, arg2, arg3));
 * @endcode
 */
inline auto newi(std::string name, std::vector<ExpressionPtr> args)
{
    return NewInstance::create(std::move(name), std::move(args));
}

/**
 * @brief Access member in class instance
 *
 * @param instance std::string
 * @param member std::string
 * @return MemberAccessPtr
 *
 * @code
 * prop("instance", "member");
 * @endcode
 */
inline auto prop(std::string instance, std::string member)
{
    return MemberAccess::create(std::move(instance), std::move(member));
}

/**
 * @brief Set member value in class instance
 *
 * @param member MemberAccessPtr
 * @param value ExpressionPtr
 * @return AssignmentPtr
 *
 * @code
 * setm(prop("instance", "member"), value);
 * @endcode
 */
inline auto setm(MemberAccessPtr member, ExpressionPtr value)
{
    return set(std::move(member), std::move(value));
}

/**
 * @brief Call member function in class instance
 *
 * @param member MemberAccessPtr
 * @param args std::vector<ExpressionPtr>
 * @return MemberFunctionCallPtr
 *
 * @code
 * callm(prop("instance", "method"), vars(arg1, arg2, arg3));
 * @endcode
 */
inline auto callm(MemberAccessPtr member, std::vector<ExpressionPtr> args)
{
    return MemberFunctionCall::create(std::move(member), std::move(args));
}

#endif // CPP_EVA_EXPRESSION_HELPERS_H
