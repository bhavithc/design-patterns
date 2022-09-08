#include <iostream>

class LightSwitch;
class State
{
public:
    virtual void turnOn(LightSwitch& ls)
    {
        std::cerr << "Already on \n";
    }

    virtual void turnOff(LightSwitch& ls)
    {
        std::cerr << "Already off \n";
    }
};

class OnState : public State
{
public:
    void turnOff(LightSwitch& ls) override;
};

class OffState : public State
{
public:
    void turnOn(LightSwitch& ls) override;
};

class LightSwitch
{
public:
    LightSwitch()
        : m_pState (new OffState)
    {
        
    }

    ~LightSwitch()
    {
        if (m_pState) {
            delete m_pState;
        }
    }

    void on()
    {
        if (m_pState) {
            m_pState->turnOn(*this);
        }
    }

    void off()
    {
        if (m_pState) {
            m_pState->turnOff(*this);
        }
    }

    void setState(State* pState)
    {
        m_pState = pState;
    }
private:
    State* m_pState = nullptr;
};

void OnState::turnOff(LightSwitch& ls)
{
    std::cout << "Turning off\n";
    ls.setState(new OffState());
    delete this; // bizar syntax even though it is valid
}

void OffState::turnOn(LightSwitch& ls)
{
    std::cout << "Turning on\n";
    ls.setState(new OnState());
    delete this; // bizar syntax even though it is valid
}

int main()
{
    LightSwitch ls;
    ls.off(); // Already off 
    ls.on(); // Turning on 
    ls.on(); // Already on
    ls.off(); // Turning off
    ls.off(); // Already off

    std::cout << "----------\n";

    LightSwitch ls2;
    ls2.on(); // Turning on
    ls2.off(); // Turning off

    return 0;
}