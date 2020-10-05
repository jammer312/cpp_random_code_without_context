#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class FigureFabric {
    std::map<std::string, std::function<Figure *(std::string)> > constr_map;
    FigureFabric(): constr_map{
        {"R", Rectangle::make},
        {"S", Square::make},
        {"C", Circle::make},
    } {}
public:
    static FigureFabric& factory_instance() {
        static FigureFabric factory;
        return factory;
    }
    Figure *make(const std::string &type, const std::string &params) {
        if (constr_map.find(type) != constr_map.end()) {
            return constr_map[type](params);
        }
        return NULL;
    }
};

int main() {
    std::string tmp;
    std::string tmp_type;
    std::vector<std::unique_ptr<Figure> > holder;
    auto factory = FigureFabric::factory_instance();
    while (std::cin >> tmp_type) {
        std::getline(std::cin,tmp);
        if (tmp_type.length() != 1) {
            continue;
        }
        if (Figure *ret = factory.make(tmp_type, tmp); ret) {
            holder.emplace_back(ret);
        }
    }
    std::stable_sort(holder.begin(), holder.end(),
        [](const std::unique_ptr<Figure> &a, const std::unique_ptr<Figure> &b) {
        return a->get_square() < b ->get_square();
    });

    for (std::unique_ptr<Figure> &i : holder) {
        std::cout << i->to_string() << std::endl;
    }
}