#include <iostream>
#include <string>
#include <memory>

class Mobile 
{
public:
    virtual void assembleProcessor()
    {
        std::cout << "[Default] ARM processor assembled !\n";
    }

    virtual void assembleDisplay()
    {
        std::cout << "[Default] Samsung display assembled !\n";
    }

    virtual void assembleCamera()
    {
        std::cout << "[Default] Sony camera assembled \n";
    }

    virtual void installOs()
    {
        std::cout << "[Default] Android OS installed \n";
    }
};

Mobile orderMobile()
{
    Mobile mobile;
    mobile.assembleProcessor();
    mobile.assembleDisplay();
    mobile.assembleCamera();
    mobile.installOs();
    return mobile;
}


// Now we want to introduce custom mobile
class SamsungMobile : public Mobile
{
public:
    void assembleProcessor() override
    {
        std::cout << "ARM processor assembled !\n";
    }

    void assembleDisplay() override
    {
        std::cout << "Samsung display assembled !\n";
    }

    void assembleCamera() override
    {
        std::cout << "Samsung camera assembled \n";
    }

    void installOs() override
    {
        std::cout << "Android OS installed with One UI \n";
    }
};

class Iphone : public Mobile
{
public:
    void assembleProcessor() override
    {
        std::cout << "A15 Bionic processor assembled !\n";
    }

    void assembleDisplay() override
    {
        std::cout << "Retina display assembled !\n";
    }

    void assembleCamera() override
    {
        std::cout << "Qualcom camera assembled \n";
    }

    void installOs() override
    {
        std::cout << "IOS installed \n";
    }
};

std::shared_ptr<Mobile> orderMobileV2(std::string type)
{
    std::shared_ptr<Mobile> mobile;
    if (type == "samsung") {
        std::cout << "Creating samsung mobile ...\n";
        mobile = std::make_shared<SamsungMobile>();
    } else if (type == "iphone") {
        std::cout << "Creating iphone mobile ...\n";
        mobile = std::make_shared<Iphone>();
    }

    mobile->assembleProcessor();
    mobile->assembleDisplay();
    mobile->assembleCamera();
    mobile->installOs();

    return mobile;
}


// Now lets remove the all condition and keep in seperate class called factory
class MobileFactory
{
public:
    // This is not a factory design pattern it is a programming technique 
    // Many people thinks that it is factory pattern, but it is not
    std::shared_ptr<Mobile> createMobile(std::string type) // Can be static function
    {
        std::shared_ptr<Mobile> mobile;
        if (type == "samsung") {
            std::cout << "Creating samsung mobile ...\n";
            mobile = std::make_shared<SamsungMobile>();
        } else if (type == "iphone") {
            std::cout << "Creating iphone mobile ...\n";
            mobile = std::make_shared<Iphone>();
        }

        return mobile;
    }
};

class MobileStore
{
public:
    MobileStore(MobileFactory& factory)
        : m_mobileFactory(factory)
    {

    }

    std::shared_ptr<Mobile> orderMobileV3(std::string type)
    {
        auto mobile = m_mobileFactory.createMobile(type);
        mobile->assembleProcessor();
        mobile->assembleDisplay();
        mobile->assembleCamera();
        mobile->installOs();
        return mobile;
    }
private:
    MobileFactory& m_mobileFactory;
};


int main()
{
    // auto mobilev1 = orderMobile();
    // auto mobilev2 =  orderMobileV2("samsung");

    MobileFactory mobileFactory;
    MobileStore mobileStore(mobileFactory);
    auto mobileV3 = mobileStore.orderMobileV3("iphone");

    return 0;
}