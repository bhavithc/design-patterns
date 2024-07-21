#include <iostream>

class Rectangle {
public:
    virtual void setWidth(double width) {
        this->width = width;
    }

    virtual void setHeight(double height) {
        this->height = height;
    }

    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }

    // Core logic of parent and should not alter by derived class 
    // making so break the LISCOV
    double area() const {
        return width * height;
    }

private:
    double width;
    double height;
};

class Square : public Rectangle {
public:
    void setWidth(double width) override {
        // altering the parent width and height
        Rectangle::setWidth(width);
        Rectangle::setHeight(width);
    }

    void setHeight(double height) override {
        // altering the parent width and height
        Rectangle::setHeight(height);
        Rectangle::setWidth(height);
    }
};

Rectangle* getRectangle()
{
    // Here when derived class is set, the meaning of parent its self is gone
    // Name says Rectangle but doing square job, because square made alter to 
    // parent class state
    return new Square;

    // offcourse happening because of run time polymorphism 
}

int main()
{
    // example 1
    Rectangle*  p = getRectangle();
    p->setHeight(12);
    p->setWidth(10);
    std::cout << "Area of reactangle : " << p->area() << "\n";
    delete p;

    // example 1
    Rectangle* q =  new Square;
    q->setHeight(12);
    q->setWidth(10);
    Rectangle* r = (Rectangle*)q;
    std::cout << "Area of reactangle : " << r->area() << "\n";
    delete q;
    q = nullptr;
    r = nullptr;

    return 0;
}
