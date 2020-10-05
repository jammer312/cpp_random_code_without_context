#include <algorithm>

template<typename T>
class Coord {
public:
    using value_type = T;
    T row, col;
    Coord(T row = T{}, T col = T{}): row(row), col(col) {}
};

template<typename T>
T dist1d(const T &len, T c1, T c2) {
    if (c1 > c2) {
        std::swap(c1, c2);
    }
    return std::min(std::abs(c2 - c1), std::abs(len - c2 + c1));
}

template<typename T>
T dist(const Coord<T> &size, const Coord<T> &c1, const Coord<T> &c2) {
    T d1 = dist1d(size.row, c1.row, c2.row);
    T d2 = dist1d(size.col, c1.col, c2.col);
    return std::max(d1, d2);
}

