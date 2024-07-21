#include <iostream>

class IPaymentGateway {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~IPaymentGateway() = default;
};

class PayPalPaymentGateway : public IPaymentGateway {
public:
    void processPayment(double amount) override 
    {
        std::cout << "Processing rs." << amount << " from paypal please wait\n";
        std::cout << "Payment success!\n";
    }
};

class GPayPaymentGateway : public IPaymentGateway {
public:
    void processPayment(double amount) override 
    {
        std::cout << "Processing rs." << amount << " from gpay please wait\n";
        std::cout << "Payment success!\n";
    }
};

class IOrderProcessor {
public:
    virtual void processOrder(double amount) = 0;
};

class SwiggyOrderProcessor : public IOrderProcessor {
public:
    SwiggyOrderProcessor(IPaymentGateway* paymentGateway) 
        : m_paymentGateway(paymentGateway)
    {
        std::cout << "Welcome to swiggy !\n";
    }

    void processOrder(double amount) override 
    {
        if (m_paymentGateway) {
            m_paymentGateway->processPayment(amount);
        }
    }

private:
    IPaymentGateway* m_paymentGateway {nullptr};
};

class ZomatoOrderProcessor : public IOrderProcessor {
public:
    ZomatoOrderProcessor(IPaymentGateway* paymentGateway) 
        : m_paymentGateway(paymentGateway)
    {
        std::cout << "Welcome to zomato !\n";
    }

    void processOrder(double amount) override 
    {
        if (m_paymentGateway) {
            m_paymentGateway->processPayment(amount);
        }
    }

private:
    IPaymentGateway* m_paymentGateway {nullptr};
};

int main()
{
    PayPalPaymentGateway paypalPaymentGateway;
    GPayPaymentGateway gpayPaymentGateway;

    SwiggyOrderProcessor swiggyWithGpay {&gpayPaymentGateway};
    swiggyWithGpay.processOrder(100);
    std::cout << "\n";

    ZomatoOrderProcessor zomatoWithGpay {&gpayPaymentGateway};
    zomatoWithGpay.processOrder(100);
    std::cout << "\n";

    SwiggyOrderProcessor swiggyWithPayPal {&paypalPaymentGateway};
    swiggyWithPayPal.processOrder(100);
    std::cout << "\n";

    ZomatoOrderProcessor zomatoWithPayPal {&paypalPaymentGateway};
    zomatoWithPayPal.processOrder(100);
    std::cout << "\n";

    return 0;
}