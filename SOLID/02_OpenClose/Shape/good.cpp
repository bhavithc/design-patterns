#include <iostream>

class IShape
{
public:
    virtual double calculateArea() const = 0;
    virtual ~IShape() = default;
};

class Rectangle : public IShape
{
public:
    Rectangle(int width, int height)
        : m_width {width}, m_height {height}
    {

    }

    double calculateArea() const override
    {
        std::cout << "Calculating area of rectangle\n";
        return m_height * m_width;
    }

private:
    int m_width {0};
    int m_height {0};
};

class Circle : public IShape
{
public:
    Circle(int radius)
        : m_radius {radius}
    {

    }

    double calculateArea() const override
    {
        std::cout << "Calculating area of circle\n";
        return 3.14159 * m_radius * m_radius;
    }
    
private:
    int m_radius {0};
};



int main()
{
    Rectangle rectangle {10, 10};
    std::cout << "Area of rectangle of 10x10 is " <<rectangle.calculateArea() << "\n";

    Circle circle {12};
    std::cout << "Area of circle with radius 12 is " <<circle.calculateArea() << "\n";

    // Other advantage is run time polymorphism
    // By this we can do depedency injection as well
    // example:
    IShape* p = &rectangle;
    p->calculateArea();

    p = &circle;
    p->calculateArea();

    return 0;
}