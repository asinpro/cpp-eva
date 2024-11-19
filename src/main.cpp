#include <iostream>
#include <unordered_map>
#include "eva.h"
#include "tests/tests.h"

int main() {
    Eva eva;

    runTests(eva);

    // Example usage:
    auto exp = beg(
        var(foo, 10)
    );
    std::cout << std::get<int>(eva.eval(std::move(exp))) << std::endl;

    return 0;
}

