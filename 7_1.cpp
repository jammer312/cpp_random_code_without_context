#include <iostream>
#include <string>

int main() {
    std::string tmp;
    while (std::cin >> tmp) {
        bool second = false;
        bool failed = false;
        for (char c: tmp) {
            switch (c) {
                case '3':
                case '4':
                    if (second) {
                        failed = true;
                    }
                    break;
                case '1':
                case '2':
                    second = true;
                    break;
                default:
                    failed = true;
                    break;
            }
            if (failed) {
                break;
            }
        }
        std::cout << (failed ? 0 : 1) << std::endl;
    }
}