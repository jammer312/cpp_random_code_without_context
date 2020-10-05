#include <iostream>
#include <iomanip>
#include <cmath>

int
main(void)
{
    double sum{}, squares_sum{};
    double buf;
    int counter{};

    while (std::cin >> buf) {
        counter++;
        sum += buf;
        squares_sum += buf * buf;
    }

    if (counter == 0) {
        return 0;
    }

    double e = sum / counter;
    double e2 = squares_sum / counter;
    double d = e2 - e * e;

    std::cout << std::setprecision(10) << e << " " << std::setprecision(10) << std::sqrt(d) << std::endl;
}