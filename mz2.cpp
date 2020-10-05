#include <functional>

template<typename T>
auto myfilter(const T & container, 
    std::function<bool (const typename T::value_type &)> pred)
{
    T ret{};
    for (auto it = container.begin(); it != container.end(); ++it) {
        if (pred(*it)) {
            ret.insert(ret.end(), *it);
        }
    }
    return ret;
}
