#include "environment.h"

#include <utility>

using namespace std;

void Environment::define(const std::string &name, EvalResult value)
{
    vars[name] = std::move(value);
}

EvalResult Environment::lookup(const std::string &name) const
{
    return resolve(name).at(name);
}

EvalResult Environment::assign(const string &name, EvalResult value)
{
    return resolve(name)[name] = std::move(value);
}

EvalMap &Environment::resolve(const string &name)
{
    auto it = vars.find(name);
    if (it != vars.end())
    {
        return vars;
    }
    else if (parent != nullptr)
    {
        return parent->resolve(name);
    }
    else
    {
        throw std::runtime_error("Undefined variable: " + name);
    }
}
