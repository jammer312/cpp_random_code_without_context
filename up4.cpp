#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>

int main(int args, char **argv)
{
    std::vector<std::string> func;
    double R;
    long long N;
    numbers::complex C(argv[1]);
    sscanf(argv[2], "%lf", &R);
    sscanf(argv[3], "%lld", &N);
    for (int i = 4; i < args; ++i) {
        func.push_back(argv[i]);
    }
    numbers::complex offset(R, 0), old_offset(offset);
    double delta_angle = (2.0 * M_PI) / N;
    numbers::complex accumulator;
    for (int i = 1; i <= N; ++i) {
        offset = numbers::complex(R * cos(delta_angle * i), R * sin(delta_angle * i));
        accumulator += numbers::eval(func, C + offset) * (offset - old_offset);
        old_offset = offset;
    }

    std::cout << accumulator.to_string() << std::endl;
}