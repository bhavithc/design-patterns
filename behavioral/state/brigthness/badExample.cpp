#include <iostream>

class Light
{
public:
    enum class State
    {
        Off,
        Medium,
        On,
    };

    void pressOn()
    {
        if (m_state == State::Off) {
            std::cout << "Turning on the bulb !\n";
            m_state = State::Medium;
        } else if (m_state == State::On) {
            std::cout << "Bulb is on with half brightness !\n";
            m_state = State::Medium;
        } else if (m_state == State::Medium) {
            std::cout << "Bulb is turned on with full brigtness !\n";
            m_state = State::On;
        }
    }

    void pressOff()
    {
        if (m_state == State::On) {
            std::cout << "Turning off the bulb !\n";
            m_state = State::Off;
        } else if (m_state == State::Medium) {
            std::cout << "Turning off the bulb !\n";
            m_state = State::Off;
        } else if (m_state == State::Off) {
            std::cerr << "Bulb is already turned off !\n";
        }

    }
private:
    State m_state = State::Off;
};

int main()
{
    Light light;
    light.pressOff();
    light.pressOn();
    light.pressOn();
    light.pressOn();
    light.pressOn();
    light.pressOff();
    light.pressOff();
    return 0;

}