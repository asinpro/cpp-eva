#ifndef CPP_EVA_TEST_UTILS_H
#define CPP_EVA_TEST_UTILS_H

#include <cassert>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#define EASSERT(expr, value, type) assert(std::get<type>(eva.eval(expr)) == value)
#define IASSERT(expr, value) EASSERT(expr, value, int)
#define SASSERT(expr, value) EASSERT(expr, value, string)
#define NASSERT(expr) EASSERT(expr, Null{}, Null)
#define BASSERT(expr, value) EASSERT(expr, value, bool)

#endif // CPP_EVA_TEST_UTILS_H
