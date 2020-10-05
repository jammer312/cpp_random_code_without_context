#include <vector>
#include <cstdint>

void process(std::vector<int64_t> &a, int64_t treshold) {
    int increase_counter = 0;

    for (auto a_it = a.rbegin(); a_it != a.rend(); ++a_it) {
        if (*a_it >= treshold) {
            increase_counter++;
        }
    }

    a.reserve(a.size() + increase_counter);
    for (auto a_it = a.rbegin(); a_it != a.rend(); ++a_it) {
        if (*a_it >= treshold) {
            a.push_back(*a_it);
        }
    }
}