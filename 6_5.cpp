#include <array>
#include <complex>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

namespace Equations {

    constexpr float eps_modifier = 32;

    template <typename T>
    bool is_zero(const std::complex<T> &in) {
        auto EPS = T{eps_modifier} * std::numeric_limits<T>::epsilon();
        return std::norm(in) < EPS;
    }

    template <typename T>
    std::pair<bool, std::vector<std::complex<T> > >
    quadratic(std::array<std::complex<T>, 3> in) {
        using container_type = std::vector<std::complex<T> >;
        if (is_zero(in[2])) {
            if (is_zero(in[1])) {
                if (is_zero(in[0])) {
                    return std::make_pair(false, container_type{});
                }
                return std::make_pair(true, container_type{});
            }
            return std::make_pair(true, container_type{-in[0] / in[1]});
        }
        auto sqD = std::sqrt(std::pow(in[1], 2) - std::complex<T>{4} * in[2] * in[0]);
        auto sol1 = (-in[1] + sqD) / (std::complex<T>{2} * in[2]);
        auto sol2 = (-in[1] - sqD) / (std::complex<T>{2} * in[2]);
        return std::make_pair(true, container_type{sol1, sol2});
    }

}
