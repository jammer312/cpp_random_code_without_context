#include <type_traits>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace RangeImpl {
    template <typename T, typename = void>
    struct acceptable : std::false_type{};
    
    //user type
    template <typename T>
    struct acceptable<T, typename std::enable_if<
        std::is_class<T>::value &&
        std::is_convertible<T, decltype(-std::declval<T>())>::value &&
        std::is_convertible<T, decltype(std::declval<T>() + std::declval<T>())>::value &&
        std::is_convertible<T, decltype(std::declval<T>() - std::declval<T>())>::value &&
        std::is_convertible<T, decltype(std::declval<T>() * std::declval<T>())>::value &&
        std::is_convertible<bool, decltype(std::declval<T>() > std::declval<T>())>::value &&
        std::is_convertible<bool, decltype(std::declval<T>() < std::declval<T>())>::value &&
        std::is_convertible<T, decltype(T(std::declval<std::string>()))>::value
    >::type> : std::true_type{};

    template <typename T>
    struct acceptable<T, typename std::enable_if<
        std::is_integral<T>::value &&
        std::is_signed<T>::value>::type> : std::true_type{};
}

template<typename T, typename = void>
class Range {};

template<typename T>
class Range <T, typename std::enable_if<RangeImpl::acceptable<T>::value>::type> {
    static constexpr bool builtin = std::is_integral<T>::value;
    T low, high;
    template<typename Y>
    friend Range<Y> operator+(const Range<Y> &a, const Range<Y> &b);
    template<typename Y>
    friend Range<Y> operator-(const Range<Y> &a, const Range<Y> &b);
    template<typename Y>
    friend Range<Y> operator*(const Range<Y> &a, const Range<Y> &b);
public:
    Range(T low = T{}, T high = T{}): low(low), high(high) {

        if (low > high) {
            throw std::invalid_argument("low > high");
        }
    }
    
    explicit Range(std::string in): low{}, high{} {
        char buf;
        std::stringstream stream_in(in);
        if (!(stream_in >> buf) || buf != '(') {
            throw std::invalid_argument("invalid format");
        }
        if (!(stream_in >> low)) {
            if (builtin && low != 0) {
                throw std::range_error("overflow");
            }
        }
        if (!(stream_in >> buf) || buf != ',') {
            throw std::invalid_argument("invalid format");
        }
        if (!(stream_in >> high)) {
            if (builtin && high != 0) {
                throw std::range_error("overflow");
            }
        }
        if (!(stream_in >> buf) || buf != ')') {
            throw std::invalid_argument("invalid format");
        }
    }
    
    std::string to_string() const {
        std::stringstream ss;
        ss << '(' << low << ',' << high << ')';
        return ss.str();
    }
    
    T get_low() const {
        return low;
    }

    T get_high() const {
        return high;
    }

    Range<T> operator-() const {
        T new_low, new_high;
        if (builtin) {        
            if (__builtin_mul_overflow(high, -1, &new_low) ||
                __builtin_mul_overflow(low, -1, &new_high)) {
                throw std::overflow_error{"overflow in unary minus"};
            }
        } else {
            new_low = -high;
            new_high = -low;
        }
        return Range<T>(new_low, new_high);
    }
};

template <typename T>
Range<T> operator+(const Range<T> &a, const Range<T> &b) {
    T new_low, new_high;
    if (Range<T>::builtin) {    
        if (__builtin_add_overflow(a.low, b.low, &new_low) ||
            __builtin_add_overflow(a.high, b.high, &new_high)) {
                throw std::overflow_error{"overflow in binary plus"};
        }
    } else {
        new_low = a.low + b.low;
        new_high = a.high + b.high;
    }
    return Range<T>(new_low, new_high);
}

template <typename T>
Range<T> operator-(const Range<T> &a, const Range<T> &b) {
    T new_low, new_high;
    if (Range<T>::builtin) {
        if (__builtin_sub_overflow(a.low, b.high, &new_low) ||
            __builtin_sub_overflow(a.high, b.low, &new_high)) {
            throw std::overflow_error("overflow in binary minus");
        }
    } else {
        new_low = a.low - b.high;
        new_high = a.high - b.low;
    }
    return Range<T>(new_low, new_high);
}

template <typename T>
Range<T> operator*(const Range<T> &a, const Range<T> &b) {
    T b1, b2, b3, b4;
    if (Range<T>::builtin) {        
        if (__builtin_mul_overflow(a.low, b.low, &b1) ||
            __builtin_mul_overflow(a.low, b.high, &b2) ||
            __builtin_mul_overflow(a.high, b.low, &b3) ||
            __builtin_mul_overflow(a.high, b.high, &b4)) {
            throw std::overflow_error("overflow in binary mul");
        }
    } else {
        b1 = a.low * b.low;
        b2 = a.low * b.high;
        b3 = a.high * b.low;
        b4 = a.high * b.high;
    }
    return Range<T>(std::min({b1, b2, b3, b4}), std::max({b1, b2, b3, b4}));
}
template<typename T>
Range(T a, T b) -> Range<T>;
