#include <iostream>
#include <string>

class IButton
{
public:
    virtual void render() = 0;
    virtual void onClick() = 0;
};

class GtkButton : public IButton
{
public:
    void render() override
    {
        std::cout << "[GTK] Button\n";
    }

    void onClick() override
    {
        std::cout << "[GTK] button is clicked !\n";
    }
};

class QTButton : public IButton
{
public:
    void render() override
    {
        std::cout << "[QT] Button\n";
    }

    void onClick() override
    {
        std::cout << "[QT] button is clicked !\n";
    }
};


class Dialog
{
public:
    enum class Type
    {
        Qt,
        Gtk,
    };

    void render(Type type)
    {
        std::cout << "Dialog\n";
        IButton* pButton = nullptr;
        if (type == Type::Gtk) {
            pButton = new GtkButton();
        } else {
            pButton = new QTButton();
        }

        pButton->render();
        pButton->onClick();

        delete pButton;
    }
};


int main()
{
    Dialog dialog;
    dialog.render(Dialog::Type::Gtk);
    dialog.render(Dialog::Type::Qt);

    return 0;
}

