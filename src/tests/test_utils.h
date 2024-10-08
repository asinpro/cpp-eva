#ifndef CPP_EVA_TEST_UTILS_H
#define CPP_EVA_TEST_UTILS_H

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#define STRINGIFY(x) #x
#define TO_STRING_ARRAY(...) { STRINGIFY(__VA_ARGS__), __VA_ARGS__ }

#define EASSERT(expr, value, type) assert(get<type>(eva.eval(expr)) == value)
#define IASSERT(expr, value) EASSERT(expr, value, int)
#define SASSERT(expr, value) EASSERT(expr, value, string)
#define NASSERT(expr) EASSERT(expr, Null{}, Null)
#define BASSERT(expr, value) EASSERT(expr, value, bool)

#define $(...) split(#__VA_ARGS__, ' ')

auto id(std::string name) {
    return std::make_unique<Identifier>(std::move(name));
}

#define TRUE id("true")
#define FALSE id("false")
#define NONE id("null")

auto lit(EvalResult value) {
    return make_unique<Literal>(std::move(value));
}

auto var(std::string name, std::unique_ptr<Expression> value) {
    return make_unique<Assignment>(std::move(name), std::move(value));
}

auto var(std::string name, EvalResult value) {
    return var(std::move(name), lit(std::move(value)));
}

auto add(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return make_unique<BinaryOperation>('+', std::move(lhs), std::move(rhs));
}

auto add(int lhs, int rhs) {
    return add(lit(lhs), lit(rhs));
}

auto sub(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return make_unique<BinaryOperation>('-', std::move(lhs), std::move(rhs));
}

auto sub(int lhs, int rhs) {
    return sub(lit(lhs), lit(rhs));
}

auto mul(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return make_unique<BinaryOperation>('*', std::move(lhs), std::move(rhs));
}

auto mul(int lhs, int rhs) {
    return mul(lit(lhs), lit(rhs));
}

auto div(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) {
    return make_unique<BinaryOperation>('/', std::move(lhs), std::move(rhs));
}

auto diw(int lhs, int rhs) {
    return div(lit(lhs), lit(rhs));
}

template<typename ...Args>
std::vector<std::string> $$(Args... args) {
    std::vector<std::string> tokens;
    (tokens.emplace_back(std::move(args)), ...);
    return tokens;
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

#endif //CPP_EVA_TEST_UTILS_H
