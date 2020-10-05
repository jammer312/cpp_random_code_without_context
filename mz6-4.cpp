#include <cstring>

class String {
    class buffer {
        size_t ref_count;
        size_t len;
        char *buf;
    public:
        buffer(): ref_count{1}, len{0}, buf{NULL} {}
        void drop() {
            if (!--ref_count) {
                delete this;
            }
        }

        const char *read() {
            return buf;
        }

        buffer *premodify() {
            if (ref_count > 1) {
                ref_count--;
                return new buffer(*this);
            }
            return this;
        }
    };
};