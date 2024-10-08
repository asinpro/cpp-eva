#ifndef CPP_EVA_ENVIRONMENT_H
#define CPP_EVA_ENVIRONMENT_H

#include <unordered_map>
#include <string>
#include <memory>
#include <exception>
#include "eval_types.h"

class Environment {
public:
    explicit Environment(EvalMap vars, std::shared_ptr<Environment> parent = nullptr)
            : vars(std::move(vars)), parent(parent) {}

    // Add other necessary methods here
    void define(const std::string &name, EvalResult value);

    EvalResult assign(const std::string &name, EvalResult value);

    EvalResult lookup(const std::string &name) const;

private:
    const EvalMap& resolve(const std::string& name) const {
        return const_cast<Environment*>(this)->resolve(name);
    }

    EvalMap& resolve(const std::string& name);

    EvalMap vars;
    std::shared_ptr<Environment> parent;
};

#endif //CPP_EVA_ENVIRONMENT_H
