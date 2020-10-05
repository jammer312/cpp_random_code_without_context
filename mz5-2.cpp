#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

class Rectangle : public Figure {
    double a, b;
    Rectangle(double a, double b): a(a), b(b) {}
public:
    static Rectangle *make(const std::string &in) {
        std::istringstream reader(in);
        double a, b;
        reader >> a >> b;
        return new Rectangle(a, b);
    }
    double get_square() const override {
        return a * b;
    }
};

class Square : public Figure {
    double a;
    Square(double a): a(a) {}
public:
    static Square *make(const std::string &in) {
        std::istringstream reader(in);
        double a;
        reader >> a;
        return new Square(a);
    }
    double get_square() const override {
        return a * a;
    }
};

class Circle : public Figure {
    double R;
    Circle(double R): R(R) {}
public:
    static Circle *make(const std::string &in) {
        std::istringstream reader(in);
        double R;
        reader >> R;
        return new Circle(R);
    }
    double get_square() const override {
        return M_PI * R * R;
    }
};
