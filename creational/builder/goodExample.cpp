#include <iostream>
#include <string>
#include <memory>

// Suppose I want to construct a complex object lets say
// Phone

enum class Os
{
    Android,
    Ios,
    Ubuntu,
};

enum class Processor
{
    Qualcom,
    Tsmc,
    AppleSilicon,
};

enum class Battery
{
    Mah1200,
    Mah5000,
    Mah6000,
};

enum class Display
{
    Lcd,
    Led,
    Oled,
    Retina,
};

namespace Utils
{
    const char* toStr(Os os)
    {
        if (os == Os::Android)
            return "Android";
        if (os == Os::Ios)
            return "Ios";
        if (os == Os::Ubuntu)
            return "Ubuntu";
    }

    const char* toStr(Processor processor)
    {
        if (processor == Processor::AppleSilicon)
            return "AppleSilicon";
        if (processor == Processor::Qualcom)
            return "Qualcom";
        if (processor == Processor::Tsmc)
            return "Tsmc";
    }

    const char* toStr(Display display)
    {
        if (display == Display::Lcd)
            return "Lcd";
        if (display == Display::Led)
            return "Led";
        if (display == Display::Oled)
            return "Oled";
        if (display == Display::Retina)
            return "Retina";
    }
    
    const char* toStr(Battery battery)
    {
        if (battery == Battery::Mah1200)
            return "1200 Mah";
        if (battery == Battery::Mah5000)
            return "5000 Mah";
        if (battery == Battery::Mah6000)
            return "6000 Mah";
    }
}

// From here builder pattern starts

// Take out all creation steps and make as interface
class IPhonebuilder
{
public:
    virtual void buildProcessor() = 0;
    virtual void buildBattery() = 0;
    virtual void buildDisplay() = 0;
    virtual void buildOs() = 0;
};

class Phone
{
public:
    void setProcessor(Processor processor)
    {
        m_processor = processor;
    }
    void setBattery(Battery battery)
    {
        m_battery = battery;
    }
    void setDisplay(Display display)
    {
        m_display = display;
    }
    void setOs(Os os)
    {
        m_os = os;
    }

    void showDetails()
    {
        std::string details{""};
        details += "\n-------------\n";
        details += "Phone details\n";
        details += "-------------\n";
        details += "Processor: ";
        details += Utils::toStr(m_processor);
        details += "\nBattery: ";
        details += Utils::toStr(m_battery);
        details += "\nDisplay: ";
        details += Utils::toStr(m_display);
        details += "\nOS: ";
        details += Utils::toStr(m_os);
        details += "\n-------------\n";
        std::cout << details << "\n";
    }
private:
    Processor m_processor;
    Battery m_battery;
    Display m_display;
    Os m_os;
};

class AndroidPhoneBuilder : public IPhonebuilder
{
public:
    AndroidPhoneBuilder(Phone& phone)
        : m_phone(phone)
    {

    }

    void buildProcessor()
    {
        m_phone.setProcessor(Processor::Qualcom);
    }

    void buildBattery()
    {
        m_phone.setBattery(Battery::Mah6000);
    }

    void buildDisplay()
    {
        m_phone.setDisplay(Display::Oled);
    }

    void buildOs()
    {
        m_phone.setOs(Os::Android);
    }

private:
    Phone& m_phone;
};

class IosPhoneBuilder : public IPhonebuilder
{
public:
    IosPhoneBuilder(Phone& phone)
        : m_phone(phone)
    {

    }

    void buildProcessor()
    {
        m_phone.setProcessor(Processor::AppleSilicon);
    }

    void buildBattery()
    {
        m_phone.setBattery(Battery::Mah5000);
    }

    void buildDisplay()
    {
        m_phone.setDisplay(Display::Led);
    }

    void buildOs()
    {
        m_phone.setOs(Os::Ios);
    }

private:
    Phone& m_phone;
};

class PhoneManufacturer
{
public:
    PhoneManufacturer(std::shared_ptr<IPhonebuilder> phoneBuilder)
        : m_phoneBuilder(phoneBuilder)
    {

    }

    void constructPhone()
    {
        m_phoneBuilder->buildProcessor();
        m_phoneBuilder->buildDisplay();
        m_phoneBuilder->buildOs();
        m_phoneBuilder->buildBattery();
    }

private:
    std::shared_ptr<IPhonebuilder> m_phoneBuilder;
};

int main()
{
    Phone phone;
    //                               Just change to AndroidPhoneBuilder to get android construct
    //                                      ^
    //                                      |
    auto phoneBuilder = std::make_shared<IosPhoneBuilder>(phone);
    PhoneManufacturer phoneManufacturer(phoneBuilder);
    phoneManufacturer.constructPhone();

    phone.showDetails();

    return 0;
}