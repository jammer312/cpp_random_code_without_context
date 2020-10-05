class Sum {
private:
    long long val;
public:
    Sum(long long a, long long b): val (a + b) {}
    Sum(const Sum &ab, long long c) {
        val = ab.get() + c;
    }
    long long get() const {
        return val;
    }
};