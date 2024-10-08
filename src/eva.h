#ifndef CPP_EVA_EVA_H
#define CPP_EVA_EVA_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <variant>
#include <regex>
#include "transformer.h"
#include "eval_types.h"
#include "environment.h"

const auto globalEnv = std::make_shared<Environment>(EvalMap{
        {"VERSION", "0.1"},
        {"null", Null{}},
        {"true", true},
        {"false", false}
});

class Eva {
public:
    explicit Eva(std::shared_ptr<Environment> global = globalEnv)
            : global(global), _transformer(std::make_shared<Transformer>()) {}

    int evalGlobal(Expression& exp) {
        return 0;
//        return _evalBody(exp, global);
    }

    EvalResult eval(std::unique_ptr<Expression> exp, std::shared_ptr<Environment> env = nullptr);

private:
    static bool isNumber(const std::string& exp);

    static bool isString(const std::string& exp);

    static bool isVariableName(const Expression& exp);

    EvalResult _eval(std::unique_ptr<Expression> exp, std::shared_ptr<Environment> env);

    int _evalBody(const std::vector<std::string>& exp, std::shared_ptr<Environment> env) {
        // Implement body evaluation
        return 0;
    }

    int _evalBlock(const std::vector<std::string>& exp, std::shared_ptr<Environment> env) {
        // Implement block evaluation
        return 0;
    }

    std::shared_ptr<Environment> global;
    std::shared_ptr<Transformer> _transformer;
};

#endif //CPP_EVA_EVA_H
