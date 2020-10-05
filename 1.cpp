#include <vector>
#include <cstdint>

void process (const std::vector<uint64_t>  &a,
    std::vector <uint64_t> &b, int step) {
    
    auto a_it = a.cbegin();
    auto b_it = b.rbegin();

    while (a_it != a.cend() && b_it != b.rend()) {
        *b_it += *a_it;
        for (int i = 1; i < step; ++i) {
            if (++a_it == a.cend()) {
                break;
            }
        }
        if (a_it == a.cend()) {
            break;
        }
        ++a_it;
        ++b_it;
    }
}
