#include <iostream>
#include <cstring>
#include <string>
 
class StringImpl
{
    char *storage{nullptr};
    size_t size{0};
    int ptr_count{1};
public:
    StringImpl() {}
    StringImpl(const char *str) {
        size = std::strlen(str);
        storage = new char[size + 1];
        std::strcpy(storage, str);
    }
    StringImpl(const StringImpl &impl) {
        size = impl.size;
        storage = new char[size + 1];
        std::strcpy(storage, impl.storage);
    }
    StringImpl(const StringImpl &impl, const char *str) {
        size = impl.size + std::strlen(str);
        storage = new char[size + 1];
        std::strcpy(storage, impl.storage);
        std::strcpy(storage + impl.size, str);
    }
    ~StringImpl() {
        delete[] storage;
    }
    void inc_count() {
        ++ptr_count;
    }
    void dec_count() {
        --ptr_count;
    }
    bool has_links() {
        return ptr_count > 0;
    }
    char &operator[] (size_t ind) const {
        return storage[ind];
    }
    operator std::string() const {
        return std::string(storage);
    }
};
 
class String
{
    StringImpl *impl{nullptr};
    void swap(String &src) noexcept {
        std::swap(impl, src.impl);
    }
public:
    String() {}
    String(const char *str) {
        impl = new StringImpl(str);
    }
    String(const String &str) {
        impl = str.impl;
        impl->inc_count();
    }
    String(const String &str, const char *added) {
        impl = new StringImpl(*str.impl, added);
    }
    ~String() {
        if (impl) {
            impl->dec_count();
            if (!impl->has_links()) {
                delete impl;
            }
        }
    }
    String &operator=(const String &str) {
        String tmp(str);
        swap(tmp);
        return *this;
    }
    String &operator+=(const char *str) {
        String tmp(*this, str);
        swap(tmp);
        return *this;
    }
    operator std::string() const {
        if (impl) {
            return std::string(*impl);
        }
        return std::string("");
    }
    char operator[](size_t ind) const {
        return impl->operator[](ind);
    }
    char &operator[](size_t ind) {
        String tmp(*this);
        swap(tmp);
        return impl->operator[](ind);
    }
};
 
#include <iostream>
using namespace std;

int main() {
    String t1 = "abc";
    String t2 = t1;
    t2[1] = 'd';
    cout<<string(t1)<<endl;
}