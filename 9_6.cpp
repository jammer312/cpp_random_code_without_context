#include <iostream>
#include <map>
#include <utility>
#include <unordered_set>

class dfa {
public:
    using rules_type = typename std::map<std::pair<std::string, char>, std::string>;
    using end_states_type = typename std::unordered_set<std::string>;

private:
    rules_type rules;
    end_states_type end_states; 
    std::string cur_state;

    bool advance(char c) {
        rules_type::iterator rule = rules.find(std::make_pair(cur_state, c));
        if (rule == rules.end()) {
            return true;
        }
        cur_state = rule->second;
        return false;
    }

public:
    dfa(rules_type rules, end_states_type end_states, std::string cur_state):
        rules(std::move(rules)), end_states(std::move(end_states)),
        cur_state(std::move(cur_state)) {}

    struct result {
        bool good;
        size_t symbols_consumed;
        std::string end_state;
    };

    result process(std::string in) {
        for (size_t i = 0; i < in.size(); ++i) {
            if (advance(in[i])) {
                return result{false, i, cur_state};
            }
        }
        return result{end_states.count(cur_state) == 1, in.size(), cur_state};
    }
};

int main() {
    dfa::rules_type rules;
    std::string buf1, buf2;
    char buf3;
    while ((std::cin >> buf1) && buf1 != "END") {
        std::cin >> buf3 >> buf2;
        rules.emplace(std::make_pair(buf1, buf3), buf2);
    }

    dfa::end_states_type end_states;
    while ((std::cin >> buf1) && buf1 != "END") {
        end_states.emplace(buf1);
    }

    std::string initial_state, str;
    std::cin >> initial_state >> str;

    dfa checker(std::move(rules), std::move(end_states), initial_state);
    auto result = checker.process(str);
    std::cout << result.good << std::endl << result.symbols_consumed << std::endl
        << result.end_state << std::endl;
}