#include <iostream>
#include <string>
#include <memory>

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
    void render()
    {
        std::cout << " !!! Dialog !!! \n";

        auto pButton = this->createButton();
        if (pButton) {
            pButton->render();
            pButton->onClick();
        }
    }

protected:
    virtual std::shared_ptr<IButton> createButton() = 0; //Factory method
};

class GtkDialog : public Dialog
{
public:
    std::shared_ptr<IButton> createButton() override
    {
        return std::make_shared<GtkButton>();
    }
};

class QtDialog : public Dialog
{
public:
    std::shared_ptr<IButton> createButton() override
    {
        return std::make_shared<QTButton>();
    }
};

class Application
{
public:
    Application(Dialog& dialog)
        : m_dialog(dialog)
    {

    }

    void render()
    {
        m_dialog.render(); // No knowledge of Qt render or Gtk render
    }

private:
    Dialog& m_dialog;
};


int main()
{
    GtkDialog gtkDialog;
    QtDialog qtDialog;

    Application gtkApp(gtkDialog);
    gtkApp.render();


    Application qtApp(qtDialog);
    qtApp.render();

    return 0;
}

