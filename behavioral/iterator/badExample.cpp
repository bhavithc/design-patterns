#include <iostream>
#include <vector>
#include <string>

class MenuItem
{
public:
    MenuItem(){}
    MenuItem(const std::string& name, const std::string& description, bool veg, double price)
        : m_name(name)
        , m_description(description)
        , m_isVeg(veg)
        , m_price(price) {}

    std::string getname() const 
    {
        return m_name;
    }

    std::string getDescription() const
    {
        return m_description;
    }

    bool isVeg() const 
    {
        return m_isVeg;
    }

    double getPrice() const
    {
        return m_price;
    }

    friend std::ostream& operator << (std::ostream& os, const MenuItem& menuItem)
    {
        os  << menuItem.getname() << ", " << menuItem.getPrice() 
            << " -- " << menuItem.getDescription();
        return os;
    }
private:
    std::string m_name {""};
    std::string m_description {""};
    bool m_isVeg {false};
    double m_price {0.0};
};

// Srinivas implementation using array
class DinnerMenu 
{
public:
    DinnerMenu()
    {
        addItems({"Roti", "Butter roti", true, 15.0});
        addItems({"Parata", "Mydha parata", true, 18.0});
        addItems({"Veg Biriyani", "Biriyani with peas", true, 100.0});
        addItems({"Chicken Biriyani", "Boneless with more spicy", false, 150.0});
        addItems({"Curd rice", "Rice mixed with curds", true, 20.0});
    }

    void addItems(const MenuItem& menuItem)
    {
        if (m_nrOfItems >= maxItems) {
            std::cerr << "Unable to add items, Menu is already full\n";
        } else {
            m_menuItems[m_nrOfItems] = menuItem;
            m_nrOfItems++;
        }
    }

    void getMenuItems(MenuItem* pMenuItems, int items)
    {
        if (items >= maxItems || items < 0) {
            std::cerr << "Invalid number of items received !\n";
            return;
        }

        if (pMenuItems == nullptr) {
            std::cerr << "Invalid pointer received \n";
            return;
        }

        for (auto i = 0; i < items; i++) {
            pMenuItems[i] = m_menuItems[i];
        }
    }
   
private:
    static const int maxItems = 20;
    MenuItem  m_menuItems[maxItems];
    int m_nrOfItems = 0;
};

// Vishal implementation using std::vector
class BreakFastMenu 
{
public:
    BreakFastMenu()
    {
        addItems({"Idly", "Idly made with Ramanagar style", true, 30.0});
        addItems({"Vade", "Cripy vade", true, 15.0});
        addItems({"Masala dose", "Dose with added Masala", true, 45.0});
        addItems({"Egg fried rice", "Fired rice made of roasted and boiled egss", false, 60.0});
        addItems({"Rice bath", "Made up of pure rice :) ", true, 50.0});
    }

    void addItems(const MenuItem& menuItem)
    {
        m_menuItems.push_back(menuItem);
    }

    void getMenuItems(std::vector<MenuItem>& menuItems)
    {
        menuItems.clear();
        menuItems = m_menuItems;
    }

private:
    std::vector<MenuItem> m_menuItems = {};
};


class Waiter
{
public:
    void printMenu()
    {
        std::vector<MenuItem> breakFastItems = {};
        const auto dinnerItemCnt = 5;
        MenuItem dinnerItems[dinnerItemCnt];

        BreakFastMenu breakFastMenu;
        breakFastMenu.getMenuItems(breakFastItems);
        
        DinnerMenu dinnerMenu;
        dinnerMenu.getMenuItems(dinnerItems, sizeof(dinnerItems)/sizeof(dinnerItems[0]));

        std::cout << "\nBREAKFAST\n";
        for (auto& item : breakFastItems) {
            std::cout << item << "\n";
        }

        std::cout << "\nDINNER\n";
        for (int i = 0; i < dinnerItemCnt; i++) {
            std::cout << dinnerItems[i] << "\n";
        }
    }

    void printBreakFastMenu()
    {
        std::vector<MenuItem> breakFastItems = {};
        BreakFastMenu breakFastMenu;
        breakFastMenu.getMenuItems(breakFastItems);
        
        std::cout << "\nBREAKFAST\n";
        for (auto& item : breakFastItems) {
            std::cout << item << "\n";
        }
    }

    void printDinnerMenu()
    {
        const auto dinnerItemCnt = 5;
        MenuItem dinnerItems[dinnerItemCnt];
        DinnerMenu dinnerMenu;
        dinnerMenu.getMenuItems(dinnerItems, sizeof(dinnerItems)/sizeof(dinnerItems[0]));
        std::cout << "\nDINNER\n";
        for (int i = 0; i < dinnerItemCnt; i++) {
            std::cout << dinnerItems[i] << "\n";
        }
    }

    void printVegMenu()
    {
        std::vector<MenuItem> breakFastItems = {};
        const auto dinnerItemCnt = 5;
        MenuItem dinnerItems[dinnerItemCnt];

        BreakFastMenu breakFastMenu;
        breakFastMenu.getMenuItems(breakFastItems);
        
        DinnerMenu dinnerMenu;
        dinnerMenu.getMenuItems(dinnerItems, sizeof(dinnerItems)/sizeof(dinnerItems[0]));

        std::cout << "\nBREAKFAST\n";
        for (auto& item : breakFastItems) {
            if (item.isVeg()) {
                std::cout << item << "\n";
            }
        }

        std::cout << "\nDINNER\n";
        for (int i = 0; i < dinnerItemCnt; i++) {
            if (dinnerItems[i].isVeg()) {
               std::cout << dinnerItems[i] << "\n";
            }
        }
    }

    bool isItemVeg(const std::string& name)
    {

    }
};



int main()
{
    Waiter waiter;
    waiter.printMenu();

    // Now we want to
    return 0;
}