#include <algorithm>

namespace Game {

    template<typename T>
    class Coord {
    public:
        using value_type = T;
        T row, col;
        Coord(T row = T{}, T col = T{}): row(row), col(col) {}
    };

    template<typename T>
    T dist(const Coord<T> &size, Coord<T> c1, Coord<T> c2) {
        if (c1.col > c2.col) {
            std::swap(c1, c2);
        }
        T dh = c2.col - c1.col;
        T top = c1.row - (dh + c1.col % 2) / 2;
        if (c2.row >= top && c2.row <= (top + dh)) {
            return dh;
        }
        return dh + std::min(std::abs(top - c2.row), std::abs(top + dh - c2.row));
    }

}
