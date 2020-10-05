#include <iostream>
#include <algorithm>

#include <boost/date_time/gregorian/gregorian.hpp>

int main() {
    int year, month, day;
    char tmp;
    if (!(std::cin >> year >> tmp >> month >> tmp >> day)) {
        return 0;
    }
    boost::gregorian::date prev_date(year, month, day);
    unsigned long long sum = 0;
    while (std::cin >> year >> tmp >> month >> tmp >> day) {
        boost::gregorian::date date(year, month, day);
        sum += std::abs((date - prev_date).days());
        prev_date = date;
    }
    std::cout << sum << std::endl;
}