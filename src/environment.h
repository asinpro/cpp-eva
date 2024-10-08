#ifndef CPP_EVA_ENVIRONMENT_H
#define CPP_EVA_ENVIRONMENT_H

#include <unordered_map>
#include <string>
#include <memory>
#include <exception>
#include "eval_types.h"

class Environment {
public:
    Environment(EvalMap vars, std::shared_ptr<Environment> parent = nullptr)
            : vars(vars), parent(parent) {}

    // Add other necessary methods here
    void define(const std::string &name, EvalResult value);

    EvalResult lookup(const std::string &name);

private:
    EvalMap vars;
    std::shared_ptr<Environment> parent;
};

#endif //CPP_EVA_ENVIRONMENT_H
