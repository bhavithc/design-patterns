#include <iostream>
#include <string>
#include <memory>

class Bevarage
{
public:
    virtual double cost() = 0;
};

class Coffee : public Bevarage
{
public:
    double cost() override
    {
        return baseCost;
    }
private:
    const double baseCost = 10.0;
};

class Tea : public Bevarage
{
public:
    double cost() override
    {
        return baseCost;
    }
private:
    const double baseCost = 8.5;
};

class AddonDecorator : public Bevarage
{
public:
    AddonDecorator(std::shared_ptr<Bevarage> pBeverage)
        : m_pBeverage(pBeverage)
    {

    }
    virtual double cost() override = 0;
protected:
    std::shared_ptr<Bevarage> m_pBeverage {};
};

class WithSugar : public AddonDecorator
{
public:
    WithSugar(std::shared_ptr<Bevarage> pBevarage)
        : AddonDecorator(pBevarage)
    {

    }

    double cost() override
    {
        return m_pBeverage->cost() + 5.0;
    }
};

class WithLemon : public AddonDecorator
{
public:
    WithLemon(std::shared_ptr<Bevarage> pBevarage)
        : AddonDecorator(pBevarage)
    {

    }

    double cost() override
    {
        return m_pBeverage->cost() + 20.0;
    }
};

int main()
{
    auto pCofee = std::make_shared<Coffee>();
    std::cout << "Coffee cost: " << pCofee->cost() << "\n";
    auto pCoffeeWithSugar = std::make_shared<WithSugar>(pCofee);
    std::cout << "Coffee with sugar: " << pCoffeeWithSugar->cost() << "\n";

    auto pTea = std::make_shared<Tea>();
    std::cout << "Tea cost: " << pTea->cost() << "\n";
    auto pLemonTea = std::make_shared<WithLemon>(pTea);
    std::cout << "Lemon tea cost: " << pLemonTea->cost() << "\n";

    // Magic, we can decorate tea with sugar as well
    auto pSugarTea = std::make_shared<WithSugar>(pTea);
    std::cout << "Tea with sugar: " << pSugarTea->cost() << "\n";

    // Can we decorate coffee with lemon? offcourse yes, but you have bad taste
    // But this was possible earlier using interface segregation but here 
    // dynamically we are doing on the existing instances with out touching exisiting
    // code

    return 0;
}