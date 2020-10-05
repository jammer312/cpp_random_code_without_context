#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <cctype>

int main() {
    std::pair<char, std::string> buf{};
    std::unordered_set<char> reachable{};
    std::vector<std::pair<char, std::string> > rules{};
    while ((std::cin >> buf.first) && (std::cin >> buf.second)) {
        rules.push_back(buf);
    }
    reachable.insert('S');
    bool not_done = true;
    while (not_done) {
        not_done = false;
        for (auto &p: rules) {
            if (reachable.count(p.first) == 0) {
                continue;
            }
            for (char c: p.second) {
                if (isupper((unsigned char) c)) {
                    not_done = not_done || reachable.insert(c).second;
                }
            }
        }
    }
    for (auto &p : rules) {
        if (reachable.count(p.first) == 1) {
            std::cout << p.first << " " << p.second << std::endl;
        }
    }
}