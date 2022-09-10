#include <iostream>
#include <array>

// Provided by vendor
class Light
{
public:
    void on()
    {
        std::cout << "Light on \n";
    }
    void off()
    {
        std::cout << "Light off \n";
    }
};

// Provided by vendor
class GarageDoor
{
public:
    void up()
    {
        std::cout << "Garage door up \n";
    }
    void down()
    {
        std::cout << "Garage door down \n";
    }
    void stop()
    {
        std::cout << "Garage door stop \n";
    }
    void lightOn()
    {
        std::cout << "Garage light on \n";
    }
    void lightOff()
    {
        std::cout << "Garage light off \n";
    }
};

class Sterio
{
public:
    void on()
    {
        std::cout << "Sterio on \n";
    }
    void off()
    {
        std::cout << "Sterio off \n";
    }
    void setVolume()
    {
        std::cout << "Sterio volume set \n";
    }
};

class RemoteControl
{
public:

    RemoteControl()
    {
        m_operations[0] = Operations::Light;
        m_operations[1] = Operations::GarageDoor;
        m_operations[2] = Operations::GarageLight;
    }

    void buttonOnPressed(int index)
    {
        if (index >= m_operations.size() || index < 0) {
            std::cerr << "Invalid operation !\n";
            return;
        }

        switch (m_operations[index])
        {
        case Operations::Light:
            lightButton(ButtonState::On);
            break;
        case Operations::GarageDoor:
            garageDoor(ButtonState::On);
            break;
        case Operations::GarageLight:
            garageLight(ButtonState::On);
            break;
        default:
            break;
        }
    }

    void buttonOffPressed(int index)
    {
        if (index >= m_operations.size() || index < 0) {
            std::cerr << "Invalid operation !\n";
            return;
        }

        switch (m_operations[index])
        {
        case Operations::Light:
            lightButton(ButtonState::Off);
            break;
        case Operations::GarageDoor:
            garageDoor(ButtonState::Off);
            break;
        case Operations::GarageLight:
            garageLight(ButtonState::Off);
            break;
        default:
            break;
        }
    }

private:
    enum class ButtonState
    {
        On,
        Off,
    };

    enum class Operations
    {
        Light,
        GarageDoor,
        GarageLight,
    };

    void lightButton(ButtonState btnState)
    {
        switch (btnState)
        {
        case ButtonState::On:
            m_light.on();
            break;
        
        case ButtonState::Off:
            m_light.off();
            break;

        default:
            break;
        }
    }

    void garageDoor(ButtonState btnState)
    {
        switch (btnState)
        {
        case ButtonState::On:
            m_garageDoor.up();
            break;
        
        case ButtonState::Off:
            m_garageDoor.down();

        // How to handle stop ?
        default:
            break;
        }
    }

    void garageLight(ButtonState btnState)
    {
        switch (btnState)
        {
        case ButtonState::On:
            m_garageDoor.lightOn();
            break;
        
        case ButtonState::Off:
            m_garageDoor.lightOff();
        default:
            break;
        }
    }

    void garageDoorStop(ButtonState btnState)
    {
        switch (btnState)
        {
        case ButtonState::On:
            m_garageDoor.stop();
            break;
        
        case ButtonState::Off:
        default:
            break;
        }
    }

private:
    Light m_light;
    Sterio m_sterio;
    GarageDoor m_garageDoor;
    std::array<Operations, 3> m_operations;
};

int main()
{
    // see the complexity 
    // How can we add undo operation in this OMG
    RemoteControl rc;
    rc.buttonOnPressed(0);
    rc.buttonOffPressed(0);

    rc.buttonOnPressed(1);
    rc.buttonOffPressed(1);
}