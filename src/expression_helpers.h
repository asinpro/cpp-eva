#ifndef CPP_EVA_EXPRESSION_HELPERS_H
#define CPP_EVA_EXPRESSION_HELPERS_H

#include <vector>
#include <string>
#include <memory>

#define TRUE id(true)
#define FALSE id(false)
#define NONE id(null)

#define ID_NAME(name) #name
#define var(name, value) $var(#name, value)
#define id(name) $id(ID_NAME(name))
#define set(name, value) $set(#name, value)
#define def(name, args, body) $def(#name, args, body)
#define call(name, ...) $call(#name, __VA_ARGS__)

template<typename ...Args>
inline auto print(Args&&... args) {
    (std::cout << ... << args) << std::endl;
    return std::make_unique<Expression>();
}

inline auto lit(EvalResult value) {
    return std::make_unique<Literal>(std::move(value));
}

inline auto wrap(std::unique_ptr<Expression> value) {
    return std::move(value);
}

inline auto wrap(EvalResult value) {
    return lit(std::move(value));
}

template<typename ...Args>
inline auto beg(Args&&... args) {
    std::vector<std::unique_ptr<Expression>> expressions;
    (expressions.push_back(std::forward<Args>(args)), ...);
    return std::make_unique<Block>(std::move(expressions));
}

inline auto iff(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> then, std::unique_ptr<Expression> otherwise) {
    return std::make_unique<Condition>(std::move(condition), std::move(then), std::move(otherwise));
}

inline std::unique_ptr<Expression> loop(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> body) {
//    return iff(std::move(condition), beg(std::move(body), loop(std::make_unique<Condition>(*condition)), std::move(body))), lit(Null{}));
    return std::make_unique<Loop>(std::move(condition), std::move(body));
}

inline auto $id(std::string name) {
    return std::make_unique<Identifier>(std::move(name));
}

inline auto $var(std::string name, std::unique_ptr<Expression> value) {
    return std::make_unique<VariableDeclaration>(std::move(name), std::move(value));
}

inline auto $var(std::string name, EvalResult value) {
    return $var(std::move(name), lit(std::move(value)));
}

inline auto $set(std::string name, std::unique_ptr<Expression> value) {
    return std::make_unique<Assignment>(std::move(name), std::move(value));
}

inline auto $set(std::string name, EvalResult value) {
    return $set(std::move(name), lit(std::move(value)));
}

inline auto gt(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('>', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto gt(T&& lhs, U&& rhs) {
    return gt(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto gte(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('+', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto gte(T&& lhs, U&& rhs) {
    return gte(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto lt(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('<', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto lt(T&& lhs, U&& rhs) {
    return lt(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto lte(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('-', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto lte(T&& lhs, U&& rhs) {
    return lte(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto eq(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('=', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto eq(T&& lhs, U&& rhs) {
    return eq(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto neq(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('!', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto neq(T&& lhs, U&& rhs) {
    return neq(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto add(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('+', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto add(T&& lhs, U&& rhs) {
    return add(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto sub(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('-', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto sub(T&& lhs, U&& rhs) {
    return sub(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto mul(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('*', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto mul(T&& lhs, U&& rhs) {
    return mul(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto divv(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return std::make_unique<BinaryOperation>('/', std::move(lhs), std::move(rhs));
}

template<typename T, typename U>
inline auto divv(T&& lhs, U&& rhs) {
    return divv(wrap(std::forward<T>(lhs)), wrap(std::forward<U>(rhs)));
}

inline auto $def(std::string name, std::vector<std::string> args, std::unique_ptr<Expression> body) {
    return std::make_unique<FunctionDefinition>(std::move(name), std::move(args), std::move(body));
}

template<typename ...Args>
inline auto args(Args&&... args) {
    std::vector<std::string> names;
    (names.push_back(std::forward<Args>(args)), ...);
    return names;
}

template<typename ...Args>
inline auto vars(Args&&... args) {
    std::vector<std::unique_ptr<Expression>> expressions;
    (expressions.push_back(wrap(std::forward<Args>(args))), ...);
    return expressions;
}

template<typename ...Args>
inline auto $call(std::string name, Args&&... args) {
    return std::make_unique<FunctionCall>(std::move(name), vars(std::forward<Args>(args)...));
}

#endif //CPP_EVA_EXPRESSION_HELPERS_H
