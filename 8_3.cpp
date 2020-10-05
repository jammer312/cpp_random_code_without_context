#include <iostream>
#include <string>

constexpr int out_bad = -1;
constexpr int out_contextual = 10;
constexpr int out_contextfree = 2;
constexpr int out_nonshortening = 3;

int main() {
    bool has_rules{}, has_starter{}, has_bad_rules{};
    bool S_generating{}, S_consuming{}, shortening{};
    bool contextual{};
    std::string left, right;
    while ((std::cin >> left) && (std::cin >> right)) {
        has_rules = true;
        for (unsigned char c: right) {
            if (c == 'S') {
                S_generating = true;
            }
        }
        if (left == "S") {
            has_starter = true;
            if (right == "_") {
                S_consuming = true;
            }
            continue;
        }
        bool has_non_terminals{};
        for (unsigned char c: left) {
            if (!(isdigit(c) || islower(c))) {
                has_non_terminals = true;
                break;
            }
        }
        if (!has_non_terminals) {
            has_bad_rules = true;
            break;
        }
        if (left.length() > 1) {
            contextual = true;
        }
        if (right == "_") {
            shortening = true;
        }
    }
    if (!(has_rules && has_starter) || has_bad_rules) {
        std::cout << out_bad;
    } else if (contextual) {
        std::cout << out_contextual;
    } else {
        std::cout << out_contextfree;
        if (!((S_generating && S_consuming) || shortening)) {
            std::cout << out_nonshortening;
        }
    }
    std::cout <<std::endl;
}