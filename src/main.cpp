#include <iostream>
#include <unordered_map>
#include "eva.h"
#include "tests/tests.h"

int main() {
    Eva eva;

    runTests(eva);

//    Example usage:
//    std::vector<std::string> exp = {"begin", "var", "foo", "10"};
//    std::cout << eva.evalGlobal(exp) << std::endl;

    return 0;
}

