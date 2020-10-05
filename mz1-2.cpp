#include <iostream>

class A {
private:
    int a;
    bool print_on_destr;
public:
    A(): print_on_destr{false} {
        std::cin >> a;
    }
    A(const A &b): print_on_destr{true} {
        std::cin >> a;
        a += b.a;
    }
    ~A() {
        if (print_on_destr) {
            std::cout << a << std::endl;
        }
    }
};
