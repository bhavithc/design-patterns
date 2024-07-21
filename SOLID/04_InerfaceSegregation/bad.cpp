#include <iostream>

class Printer {
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};

class SimplePrinter : public Printer {
public:
    void print() override {
        std::cout << "Printing...\n";
        std::cout << "Done !\n";
    }

    void scan() override {
        // SimplePrinter doesn't scan
        std::cerr << "ERROR: SimplePrinter doesn't scan \n";
    }

    void fax() override {
        // SimplePrinter doesn't fax
        std::cerr << "ERROR: SimplePrinter doesn't fax\n";
    }
};

int main()
{
    // Here Printer has all the functionalities and is called fat interface
    Printer* p = new SimplePrinter();
    p->print();
    p->scan();
    p->fax();

    return 0;
}
