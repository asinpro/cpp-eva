#include "environment.h"

using namespace std;

void Environment::define(const std::string& name, EvalResult value) {
    vars[name] = value;
}

EvalResult Environment::lookup(const std::string& name) {
    if (vars.find(name) != vars.end()) {
        return vars[name];
    } else if (parent != nullptr) {
        return parent->lookup(name);
    } else {
        throw runtime_error("Undefined variable: " + name);
    }
}
