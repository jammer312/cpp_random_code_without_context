#include <cstdio>
#include <cctype>

int main() {
    int tmp;
    bool not_read = true;
    size_t zeros = 0, ones = 0, last = 0;
    bool wide = false;
    bool state = false;
    bool skip = false;
    bool reset = false;
    bool stop = false;
    while ((tmp = getchar()), !stop) {
        if (reset) {
            last = 0;
            wide = false;
            state = false;
            reset = false;
        }
        if (tmp == EOF || isspace((unsigned char) tmp)) {
            if (tmp == EOF) {
                stop = true;
            }
            if (not_read) {
                continue;
            }
            not_read = true;
            if (!skip) {            
                if (!state || (wide && last != ones)) {
                    printf("0\n");
                } else {
                    printf("1\n");
                }
            }
            reset = true;
            skip = false;
            continue;
        }
        if (skip) {
            continue;
        }
        not_read = false;
        if (tmp != '0' && tmp != '1') {
            printf("0\n");
            reset = true;
            skip = true;
            continue;
        }
        if (tmp == (state ? '1' : '0')) {
            last++;
            continue;
        }
        if (!wide) {
            (state ? ones : zeros) = last;
            if (zeros == 0) {
                printf("0\n");
                reset = true;
                skip = true;
                continue;
            }
            last = 1;
            if (state) {
                wide = true;
            }
            state = !state;
            continue;
        }
        if ((state ? ones : zeros) != last) {
            printf("0\n");
            reset = true;
            skip = true;
            continue;
        }
        last = 1;
        state = !state;
    }
}