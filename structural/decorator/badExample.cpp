#include <iostream>
#include <string>


class Bevarage
{
public:
    virtual double cost() = 0;
};

class Addon
{
public:
    virtual bool hasSugar() = 0;
    virtual bool hasLemon() = 0;
};

class CoffeeWithSugar : public Bevarage, public Addon
{
public:
    double cost() override
    {
        double cost = 10.0;
        if (hasSugar()) {
            cost += 5.5;
        }

        return cost;
    }

    // Add function
    bool hasSugar() override
    {
        return true;
    }
    bool hasLemon() override
    {
        return false;
    }
};

class TeaWithLeamon : public Bevarage, public Addon
{
public:
    double cost() override
    {
        double cost = 10.00;
        if (hasLemon()) {
            cost += 5;
        }
        return cost;
    }

    // Waste function
    bool hasSugar() override
    {
        return false;
    }

    bool hasLemon() override
    {
        return true;
    }
};

class TeaWithSugarWithoutLemon : public Bevarage, public Addon
{
public:
    double cost() override
    {
        double cost = 10.00;
        if (hasSugar()) {
            cost += 3;
        }
        return cost;
    }

    // Waste function
    bool hasSugar() override
    {
        return true;
    }

    bool hasLemon() override
    {
        return false;
    } 
};


// We want to add topping for the coffee
// One way is using booleans in interfaces i.e. hasAMilk, hashASugar, hasACaramel
// But we are touching the code which is already built.
// Also becoming fat interface, what if Coffee does not need Leamon, We dont need
// hasLemon and we leave empty -> Interface segregation failed
// Example

int main()
{
    CoffeeWithSugar coffee;
    std::cout << "Coffee with sugar cost: ";
    std::cout << coffee.cost() << "\n";

    TeaWithLeamon tea;
    std::cout << "Tea with lemon cost: ";
    std::cout << tea.cost() << "\n";

    TeaWithSugarWithoutLemon sugarTea;
    std::cout << "Tea with sugar: ";
    std::cout << sugarTea.cost() << "\n";

    return 0;
}

