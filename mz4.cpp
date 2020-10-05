#include <algorithm>
#include <vector>
#include <iterator>

template<typename T1, typename T2>
auto myremove(T1 it1, T1 it2, T2 it3, T2 it4) {
    std::vector<typename std::iterator_traits<T1>::value_type> range_copy(it1, it2);
    std::sort(range_copy.begin(), range_copy.end());
    std::unique(range_copy.begin(), range_copy.end());
    auto vit1 = range_copy.begin();
    auto vit2 = range_copy.end();
    T2 rem1 = it3;
    T2 rem2 = rem1;
    int index = 0;
    while(rem1 != it4) {
        while (vit1 != vit2 && *vit1 < index) {
            ++vit1;
        }
        if (vit1 == vit2 || *vit1 != index) {
            std::swap(*rem1, *rem2);
            ++rem2;
        }
        ++rem1;
        index++;
    }
    return rem2;
}

