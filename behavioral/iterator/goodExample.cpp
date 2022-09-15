#include <iostream>
#include <vector>
#include <string>
#include <memory>

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


// Introduce iterator interface
class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual MenuItem next() = 0;
protected:
    std::vector<MenuItem> m_menuItems = {};
};


class DinnerMenuIterator : public  Iterator
{
public:
    DinnerMenuIterator(MenuItem menuItems[], int nrOfItems);
    bool hasNext() override;
    MenuItem next() override;
private:
    int cnt = 0;
};

class BreakFastMenuIterator : public  Iterator
{
public:
    BreakFastMenuIterator(const std::vector<MenuItem>& menuItems);
    bool hasNext() override;
    MenuItem next() override;
private:
    int cnt = 0;
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

    std::shared_ptr<Iterator> createIterator()
    {
        return std::make_shared<DinnerMenuIterator>(m_menuItems, m_nrOfItems);   
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

    std::shared_ptr<Iterator> createIterator()
    {
        return std::make_shared<BreakFastMenuIterator>(m_menuItems);   
    }

private:
    std::vector<MenuItem> m_menuItems = {};
};

DinnerMenuIterator::DinnerMenuIterator(MenuItem menuItems[], int nrOfItems)
{
    for (int i = 0; i < nrOfItems; i++) {
        m_menuItems.push_back(menuItems[i]);
    }
}

bool DinnerMenuIterator::hasNext()
{
    return cnt < m_menuItems.size();
}

MenuItem DinnerMenuIterator::next()
{
    MenuItem menuItem {};
    if (hasNext()) {
        menuItem = m_menuItems[cnt];
        cnt++;
    } else {
        std::cerr << "No item exist !\n";
    }

    return menuItem;
}


BreakFastMenuIterator::BreakFastMenuIterator(const std::vector<MenuItem>& menuItems)
{
    m_menuItems = menuItems;
}

// Same logic can be reused 
bool BreakFastMenuIterator::hasNext()
{
    return cnt < m_menuItems.size();
}

MenuItem BreakFastMenuIterator::next()
{
    MenuItem menuItem {};
    if (hasNext()) {
        menuItem = m_menuItems[cnt];
        cnt++;
    } else {
        std::cerr << "No item exist !\n";
    }

    return menuItem;
}

class Waiter
{
public:
    void printMenu()
    {
        std::vector<MenuItem> breakFastItems = {};
        const auto dinnerItemCnt = 5;
        MenuItem dinnerItems[dinnerItemCnt];

        BreakFastMenu breakFastMenu;
        auto breakFastIter = breakFastMenu.createIterator();
        
        DinnerMenu dinnerMenu;
        auto dinnerIter = dinnerMenu.createIterator();

        std::cout << "\nBREAKFAST\n";

        while (breakFastIter->hasNext())
        {
            std::cout << breakFastIter->next() << "\n";
        }
        
        std::cout << "\nDINNER\n";
        while (dinnerIter->hasNext())
        {
            std::cout << dinnerIter->next() << "\n";
        }
    }

    void printBreakFastMenu()
    {
        std::vector<MenuItem> breakFastItems = {};
        BreakFastMenu breakFastMenu;
        auto breakFastIter = breakFastMenu.createIterator();
        
        std::cout << "\nBREAKFAST\n";
        while (breakFastIter->hasNext())
        {
            std::cout << breakFastIter->next() << "\n";
        }
    }

    void printDinnerMenu()
    {
        const auto dinnerItemCnt = 5;
        MenuItem dinnerItems[dinnerItemCnt];
        DinnerMenu dinnerMenu;
        auto dinnerIter =  dinnerMenu.createIterator();
        std::cout << "\nDINNER\n";
        while (dinnerIter->hasNext())
        {
            std::cout << dinnerIter->next() << "\n";
        }
    }

    void printVegMenu()
    {
        std::vector<MenuItem> breakFastItems = {};
        const auto dinnerItemCnt = 5;
        MenuItem dinnerItems[dinnerItemCnt];

        BreakFastMenu breakFastMenu;
        auto breakFastIter = breakFastMenu.createIterator();
        
        DinnerMenu dinnerMenu;
        auto dinnerIter = dinnerMenu.createIterator();

        std::cout << "\nBREAKFAST\n";
        while (breakFastIter->hasNext())
        {
            auto item = breakFastIter->next();
            if (item.isVeg()) {
                std::cout << item << "\n";
            }
        }

        std::cout << "\nDINNER\n";
        while (dinnerIter->hasNext())
        {
            auto item = dinnerIter->next();
            if (item.isVeg()) {
                std::cout << item << "\n";
            }
        }
    }

    bool isItemVeg(const std::string& name)
    {
        return false;
    }
};



int main()
{
    Waiter waiter;
    waiter.printMenu();

    // Now we want to
    return 0;
}