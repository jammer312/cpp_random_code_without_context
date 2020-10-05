#include <iostream>
#include <cstdint>

//Ackermann function

class result {
public:
    int64_t value;
    result(const int64_t& in): value{in} {}
};

int64_t func_wrapper(int64_t a, int64_t b, int64_t k);

void func(int64_t a, int64_t b, int64_t k) {
    if (k == 0) {
        throw result{a + b};
    }
    if (b == 1) {
        throw result{a};
    }
    throw result{func_wrapper(a, func_wrapper(a, b-1, k), k-1)};
}

int64_t func_wrapper(int64_t a, int64_t b, int64_t k) {
    try {
        func(a, b, k);
    }
    catch (result a) {
        return a.value;
    }
    return 0; //never happens
}

int main() {
    int64_t a, b, k;
    while (std::cin >> a >> b >> k) {
        std::cout << func_wrapper(a, b, k) << std::endl;
    }
}