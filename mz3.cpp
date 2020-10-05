#include <functional>
#include <vector>
#include <iterator>

template<typename T>
auto myfilter2(T a, T b,
    std::function<bool (const typename std::iterator_traits<T>::value_type &)> pred)
{
    std::vector<std::reference_wrapper<typename std::iterator_traits<T>::value_type> > ret{};
    while (a != b) {
        if (pred(*a)) {
            ret.push_back(*a);
        }
        ++a;
    }
    return ret;
}

template<typename T>
void myapply(T a, T b, std::function<void (typename std::iterator_traits<T>::value_type &)> f) {
    while (a != b) {
        f(*a);
        ++a;
    }
}
