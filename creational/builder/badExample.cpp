#include <iostream>
#include <string>

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
            return "Andrtoid";
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

class Phone
{
public:
    Phone(Os os, Processor processor, Display display, Battery battery)
        : m_os(os)
        , m_processor(processor)
        , m_display(display)
        , m_battery(battery)
    {
        m_details += "\n-------------\n";
        m_details += "Phone details\n";
        m_details += "-------------\n";
        std::cout << "Creating phone...\n";
        std::cout << "Installing processor...\n";
        m_details += "Processor: ";
        m_details += Utils::toStr(m_processor);
        std::cout << "Installing battery...\n";
        m_details += "\nBattery: ";
        m_details += Utils::toStr(m_battery);
        std::cout << "Installing display...\n";
        m_details += "\nDisplay: ";
        m_details += Utils::toStr(m_display);
        std::cout << "Installing OS...\n";
        m_details += "\nOS: ";
        m_details += Utils::toStr(m_os);
        m_details += "\n-------------\n";
    }

    void showDetails()
    {
        std::cout << m_details << "\n";
    }
private:
    Os m_os = Os::Android;
    Processor m_processor = Processor::Qualcom;
    Display m_display = Display::Lcd;
    Battery m_battery = Battery::Mah1200;
    std::string m_details{""};
};

int main()
{
    Phone androidPhone(Os::Android, Processor::Qualcom, Display::Lcd, Battery::Mah1200);
    androidPhone.showDetails();

    return 0;
}