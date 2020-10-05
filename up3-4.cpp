#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>

constexpr int fraction = 10;
constexpr int precision = 10;

template<typename T>
class avg_functor {
    int amount;
    T sum;
public:
    double get_result() {
        return sum / amount;
    }
    void operator()(const T &in) {
        amount++;
        sum += in;
    }
};

int main(void)
{
    std::vector<double> holder;
    double tmp;
    while (std::cin >> tmp) {
        holder.push_back(tmp);
    }
    auto begin = holder.begin();
    auto end = holder.end();
    int delta_size = holder.size() / fraction;
    
    std::advance(begin, delta_size);
    std::advance(end, -delta_size);

    std::sort(begin,end);

    delta_size = (holder.size() - 2 * delta_size) / fraction;

    std::advance(begin, delta_size);
    std::advance(end, -delta_size);

    auto avg = std::for_each(begin, end, avg_functor<double>());
    std::cout << std::setprecision(precision) << avg.get_result() << std::endl;
}