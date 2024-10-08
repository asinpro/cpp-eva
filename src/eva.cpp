#include "eva.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
    std::ostringstream oss;
    oss << "(";
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) {
            oss << " ";
        }
    }
    oss << ")";
    os << oss.str();
    return os;
}

bool Eva::isNumber(const std::string& exp) {
    try {
        stoi(exp);
        return true;
    } catch (invalid_argument& e) {
        return false;
    }
}

bool Eva::isString(const std::string& exp) {
    return exp[0] == '"' && exp[exp.size() - 1] == '"';
}

EvalResult Eva::eval(std::unique_ptr<Expression> exp, std::shared_ptr<Environment> env) {
    try {
        return _eval(std::move(exp), env);
    } catch (const std::exception& e) {
        cerr << "Error evaluating expression: " << /*exp <<*/ endl << "- " << e.what() << endl;
    }
    return Null{};
}

EvalResult Eva::_eval(std::unique_ptr<Expression> exp, std::shared_ptr<Environment> env) {
    if (!env) {
        env = global;
    }

    return exp->eval(env);

/*
    // math expressions
    if (exp[0] == "+") {
        auto lhs = get<int>(eval({exp[1]}, env));
        auto rhs = get<int>(eval({exp[2]}, env));
        return lhs + rhs;
    }

    if (exp[0] == "-") {
        auto lhs = get<int>(eval({exp[1]}, env));
        auto rhs = get<int>(eval({exp[2]}, env));
        return lhs - rhs;
    }

    if (exp[0] == "*") {
        auto lhs = get<int>(eval({exp[1]}, env));
        auto rhs = get<int>(eval({exp[2]}, env));
        return lhs * rhs;
    }

    if (exp[0] == "/") {
        auto lhs = get<int>(eval({exp[1]}, env));
        auto rhs = get<int>(eval({exp[2]}, env));
        return lhs / rhs;
    }

    // Block: sequence of expressions
    if (exp[0] == "begin") {
        EvalMap vars;
        auto blockEnv = make_shared<Environment>(vars, env);
        return _evalBlock(exp, blockEnv);
    }

    // Variable update: (set foo 10)
    if (exp[0] == "set") {
        // Implement here: see Lectures 6 and 15
    }

    if (isVariableName(exp)) {
        return env->lookup(exp[0]);
    }
*/
    throw runtime_error("Unknown operator: " /*+ exp[0]*/);
}

bool Eva::isVariableName(const Expression& exp) {
    return true;
//    return exp.size() == 1 && std::regex_match(exp[0], std::regex("^[a-zA-Z_][a-zA-Z0-9_]*$"));
//        return /^[+\-*/<>=a-zA-Z0-9_]+$/.test(exp);
}
