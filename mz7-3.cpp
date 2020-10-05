#include <iostream>

class S {
    int value;
    bool ok;
public:
    S() {
        ok = bool(std::cin >> value);
    }
    ~S() {
        if (ok) {
            std::cout << value << std::endl;
        }
    }
    S(S&& in) {
        ok = bool(std::cin >> value);
        if (ok && in) {
            value += in.value;
            in.ok = false;
        }
    }
    operator bool() const {
        return ok;
    }
};
