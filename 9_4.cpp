#include <iostream>

// S - > aAd
// A -> aAd
// A -> bC
// C -> bCc
// C -> c


void C(int k) {
    if (k <= 1) {
        std::cout << 'c';
        return;
    }
    std::cout << 'b';
    C(k - 2);
    std::cout << 'c';
}

void A(int k, int param) {
    if (param <= 0) {
        std::cout << 'b';
        C(k - 1);
        return;
    }
    std::cout << 'a';
    A(k - 2, param - 1);
    std::cout << 'd';
}

void S(int k, int param) {
    std::cout << 'a';
    A(k - 2, param - 1);
    std::cout << 'd' << std::endl;
}

void wrapper(int k, int i = 1) {
    if (i > k / 2 - 1) {
        return;
    }
    wrapper(k, i + 1);
    S(k, i);
}

int main() {
    int k;
    std::cin >> k;
    if (k % 2) {
        return 0;
    }
    wrapper(k);
}