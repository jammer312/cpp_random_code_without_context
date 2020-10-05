#include <cstdio>
#include <map>
#include <utility>
#include <unordered_set>
#include <string>

class dfa {
public:
    using rules_type = typename std::map<std::pair<std::string, char>, std::string>;
    using end_states_type = typename std::unordered_set<std::string>;

private:
    rules_type rules;
    end_states_type end_states; 
    std::string cur_state, initial_state;

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
        cur_state(std::move(cur_state)), initial_state(this->cur_state) {}

    bool process() {
        int buf;
        bool processed_once{};
        bool bad{};
        while (buf = getchar(), buf != EOF)
        {
            if (isspace((unsigned char) buf)) {
                if (!processed_once) {
                    continue;
                }
                break;
            }
            processed_once = true;
            if (advance(buf)) {
                bad = true;
            }
        }
        if (processed_once) {
            printf("%d\n", !bad && (end_states.count(cur_state) == 1));
        }
        return end_states.count(cur_state) == 1;
    }

    void reset() {
        cur_state = initial_state;
    }
};

int main() {
    dfa checker{
        {
            {{"abc", '0'}, "abc"},
            {{"abc", '1'}, "Abc"},

            {{"Abc", '0'}, "aBc"},
            {{"Abc", '1'}, "ABc"},
            
            {{"aBc", '0'}, "abC"},
            {{"aBc", '1'}, "AbC"},
            
            {{"ABc", '0'}, "aBC"},
            {{"ABc", '1'}, "ABC"},

            {{"abC", '0'}, "abc"},
            {{"abC", '1'}, "Abc"},
 
            {{"AbC", '0'}, "aBc"},
            {{"AbC", '1'}, "ABc"},

            {{"aBC", '0'}, "abC"},
            {{"aBC", '1'}, "AbC"},

            {{"ABC", '0'}, "aBC"},
            {{"ABC", '1'}, "ABC"},
        },
        {"abC", "aBC", "AbC", "ABC"},
        "abc"
    };
    while (!feof(stdin)) {
        checker.reset();
        checker.process();
    }
}