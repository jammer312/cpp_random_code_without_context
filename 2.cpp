#include <vector>
#include <cstdint>

void process(std::vector<int64_t> &a, int64_t treshold) {
    a.reserve(2 * a.size());
    for (auto a_it = a.rbegin(); a_it != a.rend(); ++a_it) {
        if (*a_it >= treshold) {
            a.push_back(*a_it);
        }
    }
    a.shrink_to_fit();
}