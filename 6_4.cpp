#include <cstring>
#include <experimental/propagate_const>
#include <string>
#include <vector>

class String {
private:
    class internal {
    private:
        std::vector<char> cstring;
        int ref_counter;
    public:
        internal(size_t len = 0): cstring(len + 1), ref_counter{} {
            bind();
        }
        internal(const char *data): cstring{'\0'}, ref_counter{} {
            bind();
            if (!data) {
                return;
            }
            size_t len = strlen(data);
            cstring.resize(len + 1); //include \0
            strcpy(cstring.data(), data);
        }

        void bind() {
            ref_counter++;
        }
        void unbind() {
            if (!--ref_counter) {
                delete this;
            }
        }
        internal *premodify() {
            if (ref_counter > 1) {
                return split();
            }
            return this;
        }
        internal *split() {
            internal *tmp = new internal(cstring.data());
            unbind();
            return tmp;
        }

        const char read_char(size_t index) const {
            return cstring[index];
        }
        char &modify_char(size_t index) {
            return cstring[index];
        }

        const std::string to_string() const {
            return std::string(cstring.data());
        }

        void append(const internal &in) {
            size_t tmp = cstring.size();
            cstring.resize(tmp + in.cstring.size() - 1); //-1 to not count space for \0 twice
            memmove(cstring.data() + tmp - 1, in.cstring.data(), in.cstring.size());
        }
    };

    class subscript_proxy {
        String &host;
        size_t index;
    public:
        subscript_proxy(String &host, size_t index): host{host}, index{index} {}
        operator char() const {
            return host.read_char(index);
        }
        char &operator=(const char in) {
            char &tmp = host.modify_char(index);
            tmp = in;
            return tmp;
        }
    };

    const char read_char(size_t index) const {
        return string->read_char(index);
    }
    char &modify_char(size_t index) {
        string = string->premodify();
        return string->modify_char(index);
    }

    std::experimental::propagate_const<internal *> string;

public:
    String(size_t len = 0) {
        string = new internal(len);
    }
    String(const char *data) {
        string = new internal(data);
    }
    ~String() {
        if (string) {
            string->unbind();
        }
    }
    
    String(String &&in): string(std::move(in.string)) {}    //move constructor
    String(String &in): string(in.string.get()) {           //copy constructor
        string->bind();
    }

    String &operator=(String in) {
        std::swap(in.string, string);
        return *this;
    }

    String &operator+=(const String &in) {
        string = string->premodify();
        string->append(*in.string);
        return *this;
    }


    subscript_proxy operator[](size_t index) {
        return subscript_proxy{*this, index};
    }

    char operator[](size_t index) const {
        return string->read_char(index);
    }

    operator std::string() const {
        return string->to_string();
    }
};

String operator+(String a, String b) {
    return a+=b;
}
