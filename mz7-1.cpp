#include <iostream>
#include <string>

class string_printer {
    std::string buf;
    bool ok;
public:
    string_printer() {
        ok = bool(std::cin >> buf);
    }
    bool is_ok() const {
        return ok;
    }
    ~string_printer() {
        if (ok) {
            std::cout << buf << std::endl;
        }
    }
};

void recursive_string_printer() {
    string_printer tmp{}; 
    if (!tmp.is_ok()) {
        throw 1;
    }
    recursive_string_printer();
}

int main() {
    try {
        recursive_string_printer();
    }
    catch (...) {}
}