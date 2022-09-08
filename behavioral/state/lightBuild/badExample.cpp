#include <iostream>

class LightSwitch
{
public:
    enum class State
    {
        On,
        Off,
    };

    void on()
    {
        if (m_state == State::On) {
            std::cout << "Light is already on \n";
        } else {
            std::cout << "Light is turned on \n";
            m_state = State::On;
        }
    }

    void off()
    {
        if (m_state == State::Off) {
            std::cout << "Light is already off \n";
        } else {
            std::cout << "Light is turned off \n";
            m_state = State::Off;
        }
    }
private:
    State m_state = State::Off;
};

int main()
{
    LightSwitch ls;
    ls.off();
    ls.on();
    ls.on();
    ls.off();
    ls.off();
    return 0;
}