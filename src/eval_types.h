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

/**
 * This struct is used to represent a null value.
 */
struct Null
{
};

inline bool operator==(const Null &, const Null &)
{
    return true;
}

/**
 * This struct is used to represent a function definition.
 *
 * The function definition consists of a name, a list of parameters, a body expression and an environment.
 */
struct FunctionDefinition
{
    std::string name;
    std::vector<std::string> params;
    std::shared_ptr<Expression> body;
    std::shared_ptr<Environment> env;
};

/**
 * This struct is used to represent a class definition.
 *
 * The class definition consists of a name and an environment.
 */
struct ClassDefinition
{
    std::string name;
    std::shared_ptr<Environment> env;
};

/**
 * This struct is used to represent an instance definition.
 *
 * The instance definition consists of an environment.
 */
struct InstanceDefinition
{
    std::shared_ptr<Environment> env;
};

/**
 * This type is used to represent the result of an evaluation.
 *
 * The result can be:
 * - an integer
 * - a string
 * - a boolean
 * - a null value
 * - a function definition
 * - a class definition
 * - an instance definition
 */
using EvalResult = std::variant<int, std::string, bool, Null, FunctionDefinition, ClassDefinition, InstanceDefinition>;

/**
 * This type is used to represent a map of evaluation results.
 *
 * The map is used to store variables and their values.
 */
using EvalMap = std::unordered_map<std::string, EvalResult>;

#endif // CPP_EVA_EVAL_TYPES_H
