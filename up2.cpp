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


class complex_stack
{

    class complex_stack_internal {
        int ref_counter;
        complex value;
    public:
        complex_stack_internal *subinternal;
        complex_stack_internal(const complex &val, complex_stack_internal* sub):
            ref_counter{0}, value(val), subinternal{sub} {
                if (subinternal) {
                    subinternal->bind();
                }
        }
        ~complex_stack_internal() {
            if (subinternal) {
                subinternal->unbind();
            }
        }
        void bind() {
            ref_counter++;
        }
        void unbind() {
            ref_counter--;
            if (!ref_counter) {
                delete this;
            }
        }
        const complex &get_value(size_t depth) const {
            if (depth > 0 && subinternal) {
                return subinternal->get_value(depth - 1);
            }
            return value;
        }
        size_t size() const {
            if (subinternal) {
                return subinternal->size() + 1;
            }
            return 1;
        }
    };

    complex_stack_internal* internal;
    friend complex_stack operator<<(const complex_stack &stack, const complex value);
    complex_stack_internal *extend(const complex& value) const {
        return new complex_stack_internal(value, internal);
    }
    friend complex_stack operator~(const complex_stack &stack);
    complex_stack shrink() const {
        complex_stack_internal *subinternal = NULL;
        if (internal) {
            subinternal = internal->subinternal;
        }
        complex_stack out(subinternal);
        if (subinternal) {
            subinternal->bind();
        }
        return out;
    }
    complex_stack(complex_stack_internal *i): internal{i} {
        if (internal) {
            internal->bind();
        }
    }
    friend complex operator+(const complex_stack &stack);
public:
    complex_stack(): internal{NULL} {};
    complex_stack(complex_stack &&in): internal{in.internal} {
        in.internal = NULL;
    }
    complex_stack(const complex_stack &in): internal(in.internal) {
        if (internal) {
            internal->bind();
        }
    }
    complex_stack& operator=(complex_stack in) {
        std::swap(internal, in.internal);
        return *this;
    }
    ~complex_stack() {
        if (internal) {
            internal->unbind();
        }
    }
    size_t size() const{
        if (internal) {
            return internal->size();
        }
        return 0;
    }
    const complex &operator[](int ind) const {
        return internal->get_value(size()-1-ind);
    }
};

complex_stack operator<<(const complex_stack &stack, const complex value) {
    complex_stack out(stack.extend(value));
    return out;
}

complex operator+(const complex_stack &stack) {
    return stack.internal->get_value(0);
}

complex_stack operator~(const complex_stack &stack) {
    return stack.shrink();
}

}


int main() {
    numbers::complex_stack st;
    st=~(st<<numbers::complex());
}
