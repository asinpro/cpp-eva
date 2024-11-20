#ifndef CPP_EVA_ENVIRONMENT_H
#define CPP_EVA_ENVIRONMENT_H

#include <unordered_map>
#include <string>
#include <memory>
#include <exception>
#include "eval_types.h"

/**
 * This class is used to represent an environment
 *
 * The environment is used to store variables and their values.
 */
class Environment
{
public:
    explicit Environment(EvalMap vars, std::shared_ptr<Environment> parent = nullptr)
        : vars(std::move(vars)), parent(parent) {}

    /**
     * @brief Define a variable in the environment
     *
     * @param name The name of the variable
     * @param value The value of the variable
     *
     * @return The value of the variable
     *
     * @throw std::runtime_error if the variable is already defined
     */
    void define(const std::string &name, EvalResult value);

    /**
     * @brief Assign a value to a variable in the environment
     *
     * @param name The name of the variable
     * @param value The value to assign
     *
     * @return The value of the variable
     *
     * @throw std::runtime_error if the variable is not defined
     */
    EvalResult assign(const std::string &name, EvalResult value);

    /**
     * @brief Lookup the value of a variable in the environment
     *
     * @param name The name of the variable
     *
     * @return The value of the variable
     *
     * @throw std::runtime_error if the variable is not defined
     */
    EvalResult lookup(const std::string &name) const;

private:
    const EvalMap &resolve(const std::string &name) const
    {
        return const_cast<Environment *>(this)->resolve(name);
    }

    EvalMap &resolve(const std::string &name);

    EvalMap vars;
    std::shared_ptr<Environment> parent;
};

#endif // CPP_EVA_ENVIRONMENT_H
