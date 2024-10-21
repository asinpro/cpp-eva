#ifndef CPP_EVA_EXPRESSION_HELPERS_H
#define CPP_EVA_EXPRESSION_HELPERS_H

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "expressions.h"

#define TRUE id(true)
#define FALSE id(false)
#define NONE id(null)
#define none NONE

#define ID_NAME(name) #name
#define var(name, value) $var(#name, value)
#define id(name) $id(ID_NAME(name))
#define set(name, value) $set(#name, value)
#define def(name, args, body) $def(#name, args, body)
#define call(name, ...) $call(#name, __VA_ARGS__)
#define inc(name) $inc(id(name))
#define dec(name) $dec(id(name))

#define args() {}
#define args1(a) $args(#a)
#define args2(a, b) $args(#a, #b)
#define args3(a, b, c) $args(#a, #b, #c)
#define args4(a, b, c, d) $args(#a, #b, #c, #d)
#define args5(a, b, c, d, e) $args(#a, #b, #c, #d, #e)
#define args6(a, b, c, d, e, f) $args(#a, #b, #c, #d, #e, #f)
#define args7(a, b, c, d, e, f, g) $args(#a, #b, #c, #d, #e, #f, #g)
#define args8(a, b, c, d, e, f, g, h) $args(#a, #b, #c, #d, #e, #f, #g, #h)
#define args9(a, b, c, d, e, f, g, h, i) $args(#a, #b, #c, #d, #e, #f, #g, #h, #i)

template<typename ...Args>
inline auto print(Args&&... args) {
    (std::cout << ... << args) << std::endl;
    return Expression::create();
}

inline auto lit(EvalResult value) {
    return Literal::create(std::move(value));
}

inline auto wrap(ExpressionPtr value) {
    return std::move(value);
}

inline auto wrap(EvalResult value) {
    return lit(std::move(value));
}

template<typename ...Args>
inline auto beg(Args&&... args) {
    std::vector<ExpressionPtr> expressions;
    (expressions.push_back(std::forward<Args>(args)), ...);
    return Block::create(std::move(expressions));
}

inline auto iff(ExpressionPtr condition, ExpressionPtr then, ExpressionPtr otherwise) {
    return Condition::create(std::move(condition), std::move(then), std::move(otherwise));
}

inline ExpressionPtr loop(ExpressionPtr condition, ExpressionPtr body) {
//    return iff(std::move(condition), beg(std::move(body), loop(std::make_unique<Condition>(*condition)), std::move(body))), lit(Null{}));
    return Loop::create(std::move(condition), std::move(body));
}

inline auto floop(ExpressionPtr init, ExpressionPtr condition, ExpressionPtr modifier, ExpressionPtr body) {
    return ForLoop::create(std::move(init), std::move(condition), std::move(modifier), std::move(body));
}

inline auto $id(std::string name) {
    return Identifier::create(std::move(name));
}

inline auto $var(std::string name, ExpressionPtr value) {
    return VariableDeclaration::create(std::move(name), std::move(value));
}

inline auto $var(std::string name, EvalResult value) {
    return $var(std::move(name), lit(std::move(value)));
}

inline auto $set(std::string name, ExpressionPtr value) {
    return Assignment::create(std::move(name), std::move(value));
}

inline auto $set(std::string name, EvalResult value) {
    return $set(std::move(name), lit(std::move(value)));
}

inline auto gt(ExpressionPtr lhs, ExpressionPtr rhs) {
    return BinaryOperation::create(BinaryOperationType::GREATER, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto gt(T&& lhs, U&& rhs) {
    return gt(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto gte(ExpressionPtr lhs, ExpressionPtr rhs) {
    return BinaryOperation::create(BinaryOperationType::GREATER_OR_EQUAL, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto gte(T&& lhs, U&& rhs) {
    return gte(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto lt(ExpressionPtr lhs, ExpressionPtr rhs) {
    return std::make_unique<BinaryOperation>(BinaryOperationType::LESS, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto lt(T&& lhs, U&& rhs) {
    return lt(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto lte(ExpressionPtr lhs, ExpressionPtr rhs) {
    return BinaryOperation::create(BinaryOperationType::LESS_OR_EQUAL, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto lte(T&& lhs, U&& rhs) {
    return lte(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto eq(ExpressionPtr lhs, ExpressionPtr rhs) {
    return std::make_unique<BinaryOperation>(BinaryOperationType::EQUAL, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto eq(T&& lhs, U&& rhs) {
    return eq(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto neq(ExpressionPtr lhs, ExpressionPtr rhs) {
    return std::make_unique<BinaryOperation>(BinaryOperationType::NOT_EQUAL, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto neq(T&& lhs, U&& rhs) {
    return neq(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto add(ExpressionPtr lhs, ExpressionPtr rhs) {
    return BinaryOperation::create(BinaryOperationType::ADDITION, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto add(T&& lhs, U&& rhs) {
    return add(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto sub(ExpressionPtr lhs, ExpressionPtr rhs) {
    return BinaryOperation::create(BinaryOperationType::SUBTRACTION, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto sub(T&& lhs, U&& rhs) {
    return sub(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto mul(ExpressionPtr lhs, ExpressionPtr rhs) {
    return BinaryOperation::create(BinaryOperationType::MULTIPLICATION, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto mul(T&& lhs, U&& rhs) {
    return mul(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto divv(ExpressionPtr lhs, ExpressionPtr rhs) {
    return BinaryOperation::create(BinaryOperationType::DIVISION, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto divv(T&& lhs, U&& rhs) {
    return divv(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto mod(ExpressionPtr lhs, ExpressionPtr rhs) {
    return BinaryOperation::create(BinaryOperationType::MOD, std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto mod(T&& lhs, U&& rhs) {
    return mod(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto $inc(IdentifierPtr value) {
    return Increment::create(std::move(value));
}

template<typename T>
inline auto $inc(T&& value) {
    return inc(wrap(std::forward<T>(value)));
}

inline auto $dec(IdentifierPtr value) {
    return Decrement::create(std::move(value));
}

template<typename T>
inline auto $dec(T&& value) {
    return dec(wrap(std::forward<T>(value)));
}

inline auto $def(std::string name, std::vector<std::string> args, ExpressionPtr body) {
    return FunctionDeclaration::create(std::move(name), std::move(args), std::move(body));
}

inline auto $def(std::string name, std::vector<std::string> args, EvalResult body) {
    return $def(std::move(name), std::move(args), lit(std::move(body)));
}

inline auto lambda(std::vector<std::string> args, ExpressionPtr body) {
    return Lambda::create(std::move(args), std::move(body));
}

template<typename ...Args>
inline auto $args(Args&&... args) {
    std::vector<std::string> names;
    (names.push_back(std::forward<Args>(args)), ...);
    return names;
}

template<typename ...Args>
inline auto vars(Args&&... args) {
    std::vector<ExpressionPtr> expressions;
    (expressions.push_back(wrap(std::forward<Args>(args))), ...);
    return expressions;
}

inline auto $call(std::string name, std::vector<ExpressionPtr> args) {
    return FunctionCall::create(std::move(name), std::move(args));
}

template<typename ...Args>
inline auto $call(std::string name, Args&&... args) {
    return $call(std::move(name), vars(std::forward<Args>(args)...));
}

inline auto iile(ExpressionPtr exp, std::vector<ExpressionPtr> args) {
    return AnonymousFunctionCall::create(std::move(exp), std::move(args));
}

template<typename ...Args>
inline auto iile(ExpressionPtr exp, Args&&... args) {
    return iile(std::move(exp), vars(std::forward<Args>(args)...));
}

template<typename T>
inline std::pair<ExpressionPtr, ExpressionPtr> when(ExpressionPtr condition, T&& body) {
    return std::make_pair(std::move(condition), wrap(std::forward<T>(body)));
}

template<typename T>
inline std::pair<ExpressionPtr, ExpressionPtr> any(T&& value) {
    return std::make_pair(TRUE, wrap(std::forward<T>(value)));
}

template<typename ...Args>
inline auto select(Args&&... args) {
    auto cases = std::vector<std::pair<ExpressionPtr, ExpressionPtr>>();
    (cases.push_back(std::forward<Args>(args)), ...);
    return Switch::create(std::move(cases));
}


#endif //CPP_EVA_EXPRESSION_HELPERS_H
