class Sub {
private:
    int val;
public:
    Sub(int a, int b): val{a-b} {}

    Sub(Sub a, int b): val{a.value() - b} {}

    Sub(int a, Sub b): val{a - b.value()} {}

    int value() const {
        return val;
    }
};
