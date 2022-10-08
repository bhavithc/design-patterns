#include <iostream>
#include <string>
#include <memory>
//Requirement
// Draw on Desktop and Mobile
// with following OS Linux, Apple, Windows
// Cartesian product is 3 x 2 = 6
// if 4 x 4 means we need to have 16 classes
// We can solve this problem using bridge then we have only
// 4 + 4 i.e. 8 classes

class Implementor;
class Window
{
public:
    Window(std::shared_ptr<Implementor> pImplementor)
        : m_implementor(pImplementor)
    {

    }

    virtual void draw() = 0;
protected:
    std::shared_ptr<Implementor> m_implementor;
};

// Extract the implementation out 
class Implementor
{
public:
    virtual void drawImpl() = 0;
};


class LinuxImplementor : public Implementor
{
public:
    void drawImpl() override
    {
        std::cout << "Drawing on Linux\n";
    }
};

class AppleImplementor : public Implementor
{
public:
    void drawImpl() override
    {
        std::cout << "Drawing on Apple\n";
    }
};

class WindowsImplementor : public Implementor
{
public:
    void drawImpl() override
    {
        std::cout << "Drawing on Windows\n";
    }
};

// Add GTK
// class GtkImplementor : public Implementor
// {
// public:
//     void drawImpl() override
//     {
//         std::cout << "Drawing using GTK framework \n";
//     }
// };

class Desktop : public Window
{
public:
    Desktop(std::shared_ptr<Implementor> pImplementor)
        : Window(pImplementor)
    {

    }

    void draw() override
    {
        std::cout << "------- Desktop ------ \n";
        m_implementor->drawImpl();
        std::cout << "---------------------- \n\n";
    }
};

class Mobile : public Window
{
public:
    Mobile(std::shared_ptr<Implementor> pImplementor)
        : Window(pImplementor)
    {

    }

    void draw() override
    {
        std::cout << "------- Mobile ------ \n";
        m_implementor->drawImpl();
        std::cout << "---------------------- \n\n";
    }
};


int main()
{

    auto lnxImplementor = std::make_shared<LinuxImplementor>();
    auto appleImplementor = std::make_shared<AppleImplementor>();
    auto windowsImplementor = std::make_shared<WindowsImplementor>();
    //auto gtkImplementor = std::make_shared<GtkImplementor>();

    // Desktops
    Desktop lnxDesktop(lnxImplementor);
    Desktop appleDesktop(appleImplementor);
    Desktop windowsDesktop(windowsImplementor);
    //Desktop gtkDesktop(gtkImplementor);

    // Mobiles
    Mobile androidMobile(lnxImplementor);
    Mobile appleMobile(appleImplementor);
    Mobile windowsMobile(windowsImplementor);
    //Mobile gtkMobile(gtkImplementor);

    lnxDesktop.draw();
    appleDesktop.draw();
    windowsDesktop.draw();
    //gtkDesktop.draw();

    androidMobile.draw();
    appleMobile.draw();
    windowsMobile.draw();
    //gtkMobile.draw();

    return 0;
}
