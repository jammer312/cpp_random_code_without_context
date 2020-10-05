#include <vector>
#include <string>
#include <map>
#include <functional>

namespace numbers
{
    complex eval(const std::vector<std::string> &args, const complex &z) {
        static std::map<std::string, std::function<void (complex_stack &)> > op_map{
            {"+", [] (complex_stack &stack) {
                complex tmp = +stack;
                stack = ~stack;
                tmp = +stack + tmp;
                stack = ~stack << tmp;
            }},
            {"-", [] (complex_stack &stack) {
                complex tmp = +stack;
                stack = ~stack;
                tmp = +stack - tmp;
                stack = ~stack << tmp;
            }},
            {"*", [] (complex_stack &stack) {
                complex tmp = +stack;
                stack = ~stack;
                tmp = +stack * tmp;
                stack = ~stack << tmp;
            }},
            {"/", [] (complex_stack &stack) {
                complex tmp = +stack;
                stack = ~stack;
                tmp = +stack / tmp;
                stack = ~stack << tmp;
            }},
            {"!", [] (complex_stack &stack) {
                stack = stack << +stack;
            }},
            {";", [] (complex_stack &stack) {
                stack = ~stack;
            }},
            {"~", [] (complex_stack &stack) {
                stack = ~stack << ~+stack;
            }},
            {"#", [] (complex_stack &stack) {
                stack = ~stack << -+stack;
            }},
        };
        complex_stack stack;
        for (auto i : args) {
            switch (i[0]) {
                case 'z':
                    stack = stack << z;
                    break;
                case '(':
                    stack = stack << complex(i);
                    break;
                default:
                    if (op_map.find(i) != op_map.end()) {
                        op_map[i](stack);
                    }
                    break;
            }
        }
        return +stack;
    }
}