#include <iostream>

class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height)
        : width(width), height(height) {}

    // Core logic of rectangle
    double area() const override {
        return width * height;
    }

    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }

private:
    double width;
    double height;
};

class Square : public Shape {
public:
    Square(double side)
        : side(side) {}

    // Core logic of square
    double area() const override {
        return side * side;
    }

    double getSide() const {
        return side;
    }

private:
    double side;
};


int main()
{
   // example 1
    Shape*  p = new Rectangle(10, 12);
    std::cout << "Area of reactangle : " << p->area() << "\n";

    // example 2
    Shape* q =  new Square(10);
    std::cout << "Area of square : " << q->area() << "\n";

    delete q;
    delete p;
}