#include <iostream>
#include <exception>

class Bird {
public:
    virtual void fly() {
        std::cout << "Flying" << std::endl;
    }
};

class Penguin : public Bird {
public:
    void fly() override {
        throw std::logic_error("Penguins can't fly");
    }
};

void print(Bird* b)
{
    if (b) {
        b->fly();
    }
}

int main()
{
    Bird b;
    print(&b);

    // Try to send subclass instance to parent pointer and it should not break 
    Penguin p;
    print(&p);
}