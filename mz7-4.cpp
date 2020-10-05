#include <string>
#include <iostream>
#include <map>
#include <tuple>

template <typename state, typename iterator>
class state_machine {
    using direction_type = char;
    using direction_map = std::map<direction_type, int>;
    using cell_type = typename iterator::value_type;
    using rules_type = std::map<
        std::tuple<state, cell_type>,
        std::tuple<state, cell_type, direction_type>
        >;

    state cur_state;
    iterator cur_cell, left_edge, right_edge;
    rules_type rules;
    
    void advance() {
        auto rule = rules.find({cur_state, *cur_cell});
        if (rule == rules.end()) {
            throw bad_rule{};
        }
        auto new_state = std::get<0>(rule->second);
        auto new_value = std::get<1>(rule->second);
        auto dir = std::get<2>(rule->second);
        //trivial loop check
        if (cur_state == new_state &&
            *cur_cell == new_value &&
            dir == 'S') {
            throw looped{};
        }
        if (dir != 'R' && dir != 'S' && dir != 'L') {
            throw bad_dir{dir};
        }
        cur_state = new_state;
        *cur_cell = new_value;
        switch (dir) {
            case 'R':
                ++cur_cell;
                //end style
                if (cur_cell == right_edge) {
                    throw out_of_bounds{};
                }
                break;
            case 'L':
                //begin style
                if (cur_cell == left_edge) {
                    throw out_of_bounds{};
                }
                --cur_cell;
                break;
        }
    }
    inline void eprnt(const std::string& in) {
        std::cout << "Runtime error: " << in << std::endl;
    }
public:
    class bad_rule {};
    class bad_dir {
    public:
        direction_type dir;
    };
    class out_of_bounds {};
    class looped {};
    
    state_machine(state&& start,
        iterator&& start_cell, iterator&& left_edge, iterator&& right_edge,
        rules_type&& rules):
        cur_state{std::move(start)},
        cur_cell{std::move(start_cell)},
        left_edge{std::move(left_edge)},
        right_edge{std::move(right_edge)},
        rules{std::move(rules)} {}

    bool launch() {
        try {
            while (true) {
                advance();
            }
        }
        catch (bad_rule e) {
            eprnt(std::string("No rule found for state: (") + cur_state + ", " + *cur_cell + ")");
        }
        catch (bad_dir e) {
            eprnt(std::string("Incorrect direction: ") + e.dir);
        }
        catch (out_of_bounds) {
            return false; //required to pass tests it seems ¯\_(ツ)_/¯
        }
        catch (looped) {
            return false;
        }
        return true; //error
    }
};

int main() {
    std::string tmp;
    std::cin >> tmp;
    state_machine<char, std::string::iterator>
        char_state_machine{'S', tmp.begin(), tmp.begin(), tmp.end(), {
            {{'S', '0'}, {'S', '0', 'R'}},
            {{'S', '1'}, {'A', '1', 'R'}},
            {{'S', '#'}, {'S', '#', 'R'}},
            {{'A', '0'}, {'A', '0', 'R'}},
            {{'A', '1'}, {'S', '1', 'R'}},
            {{'A', '#'}, {'B', '#', 'L'}},
            {{'B', '0'}, {'B', '0', 'L'}},
            {{'B', '1'}, {'B', '1', 'L'}},
            {{'B', '#'}, {'C', '#', 'R'}},
            {{'C', '0'}, {'C', '0', 'R'}},
            {{'C', '1'}, {'D', '0', 'S'}},
            {{'D', '0'}, {'D', '0', 'S'}}
        }};
    if (!char_state_machine.launch()) {
        std::cout << tmp << std::endl;
    }
}