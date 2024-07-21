#include <iostream>

enum class ShapeType {
    Circle,
    Rectangle
};

class Shape {
public:
    void setWidth(int width)
    {
        m_width = width;
    }

    void setHeight(int heigt)
    {
        m_height = heigt;
    }

    void setRadius(int radius)
    {
        m_radius = radius;
    }

    double calculateArea(ShapeType type) {
        switch (type) {
            case ShapeType::Circle:
                return 3.14159 * m_radius * m_radius;
            case ShapeType::Rectangle:
                return m_width * m_height;
            default:
                std::cerr << "Invalid input\n";
                return 0.0;
        }
    }

private:    
    int m_radius {0};
    int m_width {0};
    int m_height {0};
};


int main()
{
    Shape shape;
    shape.setHeight(10);
    shape.setWidth(10);
    std::cout << "Area of rectangle of 10x10 is " <<shape.calculateArea(ShapeType::Rectangle) << "\n";

    shape.setRadius(12);
    std::cout << "Area of circle with radius 12 is " <<shape.calculateArea(ShapeType::Circle) << "\n";

    return 0;
}