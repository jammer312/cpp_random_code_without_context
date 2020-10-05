#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip>

namespace numbers
{
constexpr int PRECISION = 10;

class complex {
    double real, imaginary;
public:
    complex(double re = 0., double im = 0.): real(re), imaginary(im) {}

    explicit complex(std::string in) {
        std::stringstream instream(in);
        char buf;
        instream >> buf >> real >> buf >> imaginary;
    }

    double re() const {
        return real;
    }
    double im() const {
        return imaginary;
    }
    double abs2() const {
        return real * real + imaginary * imaginary;
    }
    double abs() const {
        return std::sqrt(abs2());
    }

    std::string to_string() const {
        std::stringstream ostream;
        ostream << std::setprecision(PRECISION) << "(" << real << ","
            << std::setprecision(PRECISION) << imaginary << ")";
        return ostream.str();
    }

    complex &operator+=(const complex &in) {
        real += in.real;
        imaginary += in.imaginary;
        return *this;
    }
    complex &operator-=(const complex &in) {
        real -= in.real;
        imaginary -= in.imaginary;
        return *this;
    }
    complex &operator*=(const complex &in) {
        double tmp_re = real * in.real - imaginary * in.imaginary;
        imaginary = real * in.imaginary + imaginary * in.real;
        real = tmp_re;
        return *this;
    }
    complex &operator/=(const complex &in) {
        *this *= ~in;
        double mod = in.abs2();
        real /= mod;
        imaginary /= mod;
        return *this; 
    }
    complex operator~() const {
        return complex(real, -imaginary);
    }
    complex operator-() const {
        return complex(-real, -imaginary);
    }
};
complex operator+(const complex a, const complex b) {
    complex out{a};
    return out += b;
}
complex operator-(const complex a, const complex b) {
    complex out{a};
    return out -= b;
}
complex operator*(const complex a, const complex b) {
    complex out{a};
    return out *= b;
}
complex operator/(const complex a, const complex b) {
    complex out{a};
    return out /= b;
}
}

