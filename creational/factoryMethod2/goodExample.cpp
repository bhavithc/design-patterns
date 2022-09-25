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

class VivoMobile : public Mobile
{
public:
    void assembleProcessor() override
    {
        std::cout << "Vivo processor assembled !\n";
    }

    void assembleDisplay() override
    {
        std::cout << "Vivo LCD display assembled !\n";
    }

    void assembleCamera() override
    {
        std::cout << "Qualcom camera assembled \n";
    }

    void installOs() override
    {
        std::cout << "Android with Vivo UI installed \n";
    }
};

class Xiomi : public Mobile
{
public:
    void assembleProcessor() override
    {
        std::cout << "Xiomi processor assembled !\n";
    }

    void assembleDisplay() override
    {
        std::cout << "Xiomi display assembled !\n";
    }

    void assembleCamera() override
    {
        std::cout << "Xiomi camera assembled \n";
    }

    void installOs() override
    {
        std::cout << "Android with Xiomi UI installed \n";
    }
};

class MobileStore
{
public:
    std::shared_ptr<Mobile> orderMobile(std::string type)
    {
        auto mobile = createMobile(type);
        if (mobile) {
            mobile->assembleProcessor();
            mobile->assembleDisplay();
            mobile->assembleCamera();
            mobile->installOs();
        }
        return mobile;
    }
    // This is actual factory design pattern, let subclass decide the Mobile instance
    // This method we call as factory method
    virtual std::shared_ptr<Mobile> createMobile(const std::string& type) = 0;
};

class NewyorkMobileStore : public MobileStore
{
public:
    std::shared_ptr<Mobile> createMobile(const std::string& type) override
    {
        std::shared_ptr<Mobile> mobile {};
        if (type == "samsung") {
            std::cout << "Creating samsung mobile ...\n";
            mobile = std::make_shared<SamsungMobile>();
        } else if (type == "iphone") {
            std::cout << "Creating iphone mobile ...\n";
            mobile = std::make_shared<Iphone>();
        } else {
            std::cerr << "Unsupported mobile type received \n";
        }
        return mobile;
    }
};

class ChinaMobileStore : public MobileStore
{
public:
    std::shared_ptr<Mobile> createMobile(const std::string& type) override
    {
        std::shared_ptr<Mobile> mobile {};
        if (type == "vivo") {
            std::cout << "Creating vivo mobile ...\n";
            mobile = std::make_shared<VivoMobile>();
        } else if (type == "xiomi") {
            std::cout << "Creating xiomi mobile ...\n";
            mobile = std::make_shared<Xiomi>();
        } else {
            std::cerr << "Unsupported mobile type received \n";
        }
        return mobile;
    }
};


int main()
{
    std::shared_ptr<MobileStore> mobileStore1 = std::make_shared<NewyorkMobileStore>();
    if (mobileStore1) {
        mobileStore1->orderMobile("samsung");
        mobileStore1->orderMobile("iphone");
        mobileStore1->orderMobile("vivo"); // not supported
    }

    std::shared_ptr<MobileStore> mobileStore2 = std::make_shared<ChinaMobileStore>();
    if (mobileStore2) {
        mobileStore2->orderMobile("vivo");
        mobileStore2->orderMobile("xiomi");
        mobileStore2->orderMobile("iphone"); // not supported
    }

    return 0;
}