#include <cstdio>
#include <cctype>

// 1st type
// S -> ABCD
// A -> AAX
// XB -> BX
// XC -> CC
// B -> BBY
// YC -> CY
// YD -> DD
// A -> a
// B -> 0
// C -> b
// D -> 1

int main() {
    int buf;
    bool stop{}, bad{};
    char symbols[] = "a0b1";
    int counts[4] = {};
    int cur_state{};
    while (buf = getchar(), !stop) {
        if (buf == EOF || isspace((unsigned char) buf)) {
            stop = buf == EOF;
            if (cur_state == 0) {
                continue;
            } else if (cur_state == 4) {
                printf("%d\n", (!bad && (counts[0] == counts[2] && counts[1] == counts[3])) ? 1 : 0);
            } else {
                printf("0\n");
            }
            for (int i = 0; i < 4; ++i) {
                counts[i] = 0;
            }
            cur_state = 0;
            bad = false;
            continue;
        }
        bool found{};
        for (int i = 0; i < 4; ++i) {
            if (buf == symbols[i]) {
                found = true;
                if (cur_state != i && cur_state != i + 1) {
                    bad = true;
                }
                cur_state = i + 1;
                counts[i]++;
                break;
            }
        }
        if (!found) {
            bad = true;
        }
    }
}