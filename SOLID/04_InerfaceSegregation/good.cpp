#include <iostream>

class IPrintable {
public:
    virtual void print() = 0;
    virtual ~IPrintable() = default;
};

class IScannable {
public:
    virtual void scan() = 0;
    virtual ~IScannable() = default;
};

class IFaxable {
public:
    virtual void fax() = 0;
    virtual ~IFaxable() = default;
};

class LowBudgetPrinter : public IPrintable {
public:
    LowBudgetPrinter()
    {
        std::cout << "LowBudgetPrinter: I can only print!\n";
    }
    void print() override {
        std::cout << "Printing...\n";
        std::cout << "Done !\n";
    }
};

class MediumBudgetPrinter : public IPrintable, public IScannable {
public:
    MediumBudgetPrinter()
    {
        std::cout << "MediumBudgetPrinter: I can print and scan!\n";
    }

    void print() override
    {
        std::cout << "Printing...\n";
        std::cout << "Done !\n";        
    }

    void scan() override
    {
        std::cout << "Scanning...\n";
        std::cout << "Done !\n";        
    }
};


class HighTechPrinter : public IPrintable, public IScannable, public IFaxable
{
public:
    HighTechPrinter()
    {
        std::cout << "HighTechPrinter: I can print, scan, fax ...\n";
    }
    void print() override
    {
        std::cout << "Printing...\n";
        std::cout << "Done !\n";        
    }

    void scan() override
    {
        std::cout << "Scanning...\n";
        std::cout << "Done !\n";        
    }

    void fax() override
    {
        std::cout << "Faxing...\n";
        std::cout << "Done !\n";        
    }
};

int main()
{
    
    LowBudgetPrinter lp;
    lp.print(); // no extra functionality available
    std::cout << "\n";

    MediumBudgetPrinter mp;
    mp.print();
    mp.scan(); // no fax functionality available
    std::cout << "\n";

    HighTechPrinter hp;
    hp.print();
    hp.scan();
    hp.fax(); // All functionalities available
    std::cout << "\n";
    
    return 0;
}
