#include <iostream>

class Animal {
public:
    virtual void move() = 0;
    virtual ~Animal() = default;
};

class Bird : public Animal {
public:
    void move() override {
        std::cout << "Flying" << std::endl;
    }
};

class Penguin : public Animal {
public:
    void move() override {
        std::cout << "Swimming" << std::endl;
    }
};


void print(Animal* animal)
{
    if (animal) {
        animal->move();
    }
}

int main()
{
    Bird b;
    print(&b);

    Penguin p;
    print(&p);
}