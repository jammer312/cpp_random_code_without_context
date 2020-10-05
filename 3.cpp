#include <vector>
#include <algorithm>

void process(std::vector<int> a, std::vector<int> &b) {
    std::sort(a.begin(), a.end());
    std::unique(a.begin(), a.end());

    int b_i = 0;
    int skipped = 0;
    auto b_it = b.begin();
    auto b_dest_it = b.begin();
    auto a_it = a.begin();
    while (a_it != a.end() && *a_it < 0) {
        ++a_it;
    }
    if (a_it != a.end())
    {
        for (; b_it != b.end(); ++b_i, ++b_it) {
            if (b_i == *a_it) {
                ++skipped;
                if (++a_it == a.end()) {
                    ++b_i;
                    ++b_it;
                    break;
                }
                continue;
            }
            *b_dest_it = *b_it;
            ++b_dest_it;
        }
    }
    for (; b_it != b.end(); ++b_i, ++b_it) {
        *b_dest_it = *b_it;
        ++b_dest_it;
    }

    auto erase_it = b.end();
    erase_it -= skipped;
    b.erase(erase_it, b.end());
}