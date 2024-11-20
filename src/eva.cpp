#include "eva.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &vec)
{
    std::ostringstream oss;
    oss << "(";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        oss << vec[i];
        if (i != vec.size() - 1)
        {
            oss << " ";
        }
    }
    oss << ")";
    os << oss.str();
    return os;
}

EvalResult Eva::eval(ExpressionPtr exp, std::shared_ptr<Environment> env)
{
    try
    {
        return _eval(std::move(exp), env);
    }
    catch (const std::exception &e)
    {
        cerr << "Error evaluating expression: " << /*exp <<*/ endl
             << "- " << e.what() << endl;
    }
    return Null{};
}

EvalResult Eva::_eval(ExpressionPtr exp, std::shared_ptr<Environment> env)
{
    return exp->eval(env ? env : global);
    /*
        // Variable update: (set foo 10)
        if (exp[0] == "set") {
            // Implement here: see Lectures 6 and 15
        }
    */
}
