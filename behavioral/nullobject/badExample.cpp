#include <iostream>
#include <string>
#include <memory>

class IDisplay
{
public:
    virtual std::string getDisplayDriverName() = 0;
};

class LgDisplay : public IDisplay
{
public:
    std::string getDisplayDriverName() override
    {
        return "LG LCD Panel N5045";
    }
};

class SamsungDisplay : public IDisplay
{
public:
    std::string getDisplayDriverName() override
    {
        return "Samsung 4K Gen 20.4";
    }
};

class SonyDisplay : public IDisplay
{
public:
    std::string getDisplayDriverName() override
    {
        return "Song 8K I2C v7.9";
    }
};

class DisplayStoreFactory
{
public:

    std::shared_ptr<IDisplay> getDisplay(const std::string& companyName)
    {
        if (companyName == "Sony") {
            return std::make_shared<SonyDisplay>();
        } else if (companyName == "LG") {
            return std::make_shared<LgDisplay>();
        } else if (companyName == "Samsung") {
            return std::make_shared<SamsungDisplay>();
        } else {
            return {};
        }
    }

};

int main()
{
    std::string companyNames[] = {"Sony", "LG", "Samsung", "Oppo"};
    DisplayStoreFactory dspFactory;
    for (const auto& companyName : companyNames) {
        std::shared_ptr<IDisplay> pDisplay = dspFactory.getDisplay(companyName);

        // Here user has to handle the null pointer
        if (pDisplay) {
            std::cout << "Company name: " << companyName << ", Driver: " <<  pDisplay->getDisplayDriverName() << "\n";
        } else {
            std::cout << "Display not found for company: " << companyName << "\n";
        }
    }
    
    return 0 ;
}

