#include <iostream>
#include <string>

class Liquor;
class Grocery;
class IVisitor
{
public:
    virtual double visit(const Liquor& liquor) = 0;
    virtual double visit(const Grocery& grocery) = 0;
};

class IVisitable
{
public:
    virtual double accept(IVisitor& visitor) = 0;
};

class Liquor : public IVisitable
{
public:
    Liquor( double price)
        : m_price(price)
    {

    }

    double getPrice() const
    {
        return m_price;
    }

    double accept(IVisitor& visitor) override
    {
        // dispatch one
        return visitor.visit(*this);
    }

private:
    double m_price;
};

class Grocery : public IVisitable
{
public:
    Grocery(double price)
        : m_price(price)
    {

    }

    double getPrice() const
    {
        return m_price;
    }

    double accept(IVisitor& visitor) override
    {
        // dispatch one
        return visitor.visit(*this);
    }
private:
    double m_price;
};

class GstCalulator : public IVisitor
{
public:
    double visit(const Liquor& liquor)
    {
        // dispatch two
        const auto price = liquor.getPrice();
        return price + (price * 0.18);
    }
    
    double visit(const Grocery& grocery)
    {
        // dispatch two
        const auto price = grocery.getPrice();
        return price + (price * 0.05);
    }
};

class StateTax : public IVisitor
{
public:
    double visit(const Liquor& liquor)
    {
        // dispatch two
        const auto price = liquor.getPrice();
        return price * 0.09;
    }
    
    double visit(const Grocery& grocery)
    {
        // dispatch two
        const auto price = grocery.getPrice();
        return price * 0.025;
    }
};

int main()
{
    GstCalulator gst;
    StateTax sTax;
    Liquor tuborg(120.0); //650 ml
    Liquor oldMonk(105.0); // 180ml

    Grocery rice(2000.00);
    Grocery wheat(250.0);

    std::cout << "Price of tuborg after tax is " << tuborg.accept(gst) << "\n";
    std::cout << "Price of old monk after tax is " << oldMonk.accept(gst) << "\n";
    std::cout << "Price of rice after tax is " << rice.accept(gst) << "\n";
    std::cout << "Price of wheat after tax is " << wheat.accept(gst) << "\n";

    std::cout << "------------------------------\n";

    std::cout << "Price of tuborg after tax is " << tuborg.accept(sTax) << "\n";
    std::cout << "Price of old monk after tax is " << oldMonk.accept(sTax) << "\n";
    std::cout << "Price of rice after tax is " << rice.accept(sTax) << "\n";
    std::cout << "Price of wheat after tax is " << wheat.accept(sTax) << "\n";

    return 0;
}