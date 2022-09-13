#include <iostream>
#include <string>

class Liquor
{
public:
    Liquor( double price)
        : m_price(price)
    {

    }

    double getPriceWithTax()
    {
        return  m_price + (m_price * 0.18); //18% 
    }

    double getPrice()
    {
        return m_price;
    }
private:
    double m_price;
};

class Grocery
{
public:
    Grocery(double price)
        : m_price(price)
    {

    }

    double getPriceWithTax()
    {
        return m_price + (m_price * 0.05); // 5% GST
    }

    double getPrice()
    {
        return m_price;
    }
private:
    double m_price;
};

int main()
{
    Liquor tuborg(120.0); //650 ml
    Liquor oldMonk(105.0); // 180ml

    Grocery rice(2000.00);
    Grocery wheat(250.0);

    std::cout << "Price of tuborg after tax is " << tuborg.getPriceWithTax() << "\n";
    std::cout << "Price of old monk after tax is " << oldMonk.getPriceWithTax() << "\n";
    std::cout << "Price of rice after tax is " << rice.getPriceWithTax() << "\n";
    std::cout << "Price of wheat after tax is " << wheat.getPriceWithTax() << "\n";


    // Now let's say code is already been shipped with still more complex calculation involved
    // and we want to change / add some more taxations like CGST SGST without touching the code
    // which is already in production

    // Changing the code again brakes the open close principle

    return 0;
}