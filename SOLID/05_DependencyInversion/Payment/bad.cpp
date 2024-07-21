#include <iostream>

class GooglePaymentGateway {
public:

    GooglePaymentGateway()
    {
        std::cout << "Welcome to Google Pay payment gateway !\n";
    }

    void processPayment(double amount) 
    {
        std::cout << "Processing payment of Rs. " << amount << " please wait...\n";
        std::cout << "Payment success !\n";
    }
};

class SwiggyOrder {
public:
    SwiggyOrder() 
        : m_gpayPaymentGateway {new GooglePaymentGateway()} 
    {

    }

    ~SwiggyOrder()
    {
        delete m_gpayPaymentGateway;
    }

    void processOrder(double amount) 
    {
        if (m_gpayPaymentGateway) {
            m_gpayPaymentGateway->processPayment(amount);
        }
    }

private:
    GooglePaymentGateway* m_gpayPaymentGateway;
};


int main()
{
    SwiggyOrder sp;
    sp.processOrder(100); 

    return 0;
}