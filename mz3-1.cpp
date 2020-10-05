#include <vector>
#include <cstdint>

void process(const std::vector<uint64_t>  &a,
    std::vector <uint64_t> &b, int step) {
    
    auto a_it = a.cbegin();
    auto b_it = b.rbegin();

    while (a_it != a.cend() && b_it != b.rend()) {
        *b_it += *a_it;
        if (a.cend() - a_it <= step) {
            break;
        }
        std::advance(a_it, step);
        ++b_it;
    }
}
