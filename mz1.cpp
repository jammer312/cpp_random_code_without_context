#include <iterator>

constexpr int second_addendum_rindex = 2;
constexpr int third_addendum_rindex = 4;

template<typename T>
auto process(const T &container)
{
    typename T::value_type ret{};
    auto size = container.size();
    
    if (size == 0) {
        return ret;
    }
    auto rev_it = container.rbegin();
    ret += *rev_it;

    if (size <= second_addendum_rindex) {
        return ret;
    }
    std::advance(rev_it, second_addendum_rindex);

    ret += *rev_it;

    if (size <= third_addendum_rindex) {
        return ret;
    }
    std::advance(rev_it, third_addendum_rindex - second_addendum_rindex);
    ret += *rev_it;

    return ret;
}