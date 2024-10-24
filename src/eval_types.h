#ifndef CPP_EVA_EVAL_TYPES_H
#define CPP_EVA_EVAL_TYPES_H

#include <utility>
#include <variant>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class Environment;
class Expression;

struct Null {
};

inline bool operator==(const Null&, const Null&) {
    return true;
}

struct FunctionDefinition {
    std::string name;
    std::vector<std::string> params;
    std::shared_ptr<Expression> body;
    std::shared_ptr<Environment> env;
};

struct ClassDefinition {
    std::string name;
    std::shared_ptr<Environment> env;
};

struct InstanceDefinition {
    std::shared_ptr<Environment> env;
};

using EvalResult = std::variant<int, std::string, bool, Null, FunctionDefinition, ClassDefinition, InstanceDefinition>;
using EvalMap = std::unordered_map<std::string, EvalResult>;

#endif //CPP_EVA_EVAL_TYPES_H
