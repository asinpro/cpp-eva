#ifndef CPP_EVA_TEST_UTILS_H
#define CPP_EVA_TEST_UTILS_H

#include <cassert>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#define EASSERT(expr, value, type) assert(get<type>(eva.eval(expr)) == value)
#define IASSERT(expr, value) EASSERT(expr, value, int)
#define SASSERT(expr, value) EASSERT(expr, value, string)
#define NASSERT(expr) EASSERT(expr, Null{}, Null)
#define BASSERT(expr, value) EASSERT(expr, value, bool)

#define $(...) split(#__VA_ARGS__, ' ')
inline std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

#endif //CPP_EVA_TEST_UTILS_H
