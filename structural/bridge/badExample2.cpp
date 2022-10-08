#include <iostream>
#include <string>

class Window
{
public:
    virtual void draw() = 0;
};

//Requirement
// Draw on Desktop and Mobile
// with following OS Linux, Apple, Windows
// Cartesian product is 3 x 2 = 6
// if 4 x 4 means we need to have 16 classes

class LinuxDesktop : public Window
{
public:
    void draw() override
    {
        std::cout << "Drawing on Linux Desktop\n";
    }
};

class AppleDesktop : public Window
{
public:
    void draw() override
    {
        std::cout << "Drawing on Mac desktop\n";
    }
};

class WindowsDesktop : public Window
{
public:
    void draw() override
    {
        std::cout << "Drawing on Windows desktop \n";
    }
};

class LinuxMobile : public Window
{
public:
    void draw() override
    {
        std::cout << "Drawing on Linux mobile \n";
    }
};

class AppleMobile : public Window
{
public:
    void draw() override
    {
        std::cout << "Drawing on Apple mobile \n";
    }
};

class WindowsMobile : public Window
{
public:
    void draw() override
    {
        std::cout << "Drawing on Windows mobile \n";
    }
};

int main()
{
    LinuxDesktop ld;
    ld.draw();
    AppleDesktop ad;
    ad.draw();
    WindowsDesktop wd;
    wd.draw();

    LinuxMobile lm;
    lm.draw();
    AppleMobile am;
    am.draw();
    WindowsMobile wm;
    wm.draw();

    return 0;
}
