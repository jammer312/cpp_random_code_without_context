#include <algorithm>
#include <iostream>

int dist1d(int len, int c1, int c2) {
    if (c1 > c2) {
        std::swap(c1, c2);
    }
    return std::min(std::abs(c2 - c1), std::abs(len - c2 + c1));
}

int
main()
{
    int m, n, r1, c1, r2, c2;
    std::cin >> m >> n;
    while (std::cin >> r1 >> c1 >> r2 >> c2) {
        std::cout << dist1d(m, r1, r2) + dist1d(n, c1, c2) << std::endl;
    }
}