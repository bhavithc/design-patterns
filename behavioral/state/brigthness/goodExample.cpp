#include <iostream>

class LightSwitch;

class State
{
public:
    virtual void onPressed(LightSwitch& ls)
    {

    }

    virtual void offPressed(LightSwitch& ls)
    {

    }
};

class BrightState : public State
{
public:
    void onPressed(LightSwitch& ls) override;
    void offPressed(LightSwitch& ls) override;
};

class OffState : public State
{
public:
    void onPressed(LightSwitch& ls) override;
    void offPressed(LightSwitch& ls) override;
};

class DimmedState : public State
{
public:
    void onPressed(LightSwitch& ls) override;
    void offPressed(LightSwitch& ls) override;
};

class MediumState : public State
{
public:
    void onPressed(LightSwitch& ls) override;
    void offPressed(LightSwitch& ls) override;
};

class LightSwitch
{
public:
    LightSwitch()
        : m_pState(new OffState)
    {

    }

    ~LightSwitch()
    {
        if (m_pState) {
            delete m_pState;
        }
    }

    void pressOn()
    {
        m_pState->onPressed(*this);
    }

    void pressOff()
    {
        m_pState->offPressed(*this);
    }

    void setState(State* pState)
    {
        m_pState = pState;
    }
private:
    State* m_pState = nullptr;
};

void BrightState::onPressed(LightSwitch& ls)
{
    std::cout << "Light is dimmed \n";
    ls.setState(new DimmedState);
    delete this;
}

void BrightState::offPressed(LightSwitch& ls)
{
    std::cout << "Light is turned off \n";
    ls.setState(new OffState);
    delete this;
}

void MediumState::onPressed(LightSwitch& ls)
{
    std::cout << "Light is turned on with full brightness \n";
    ls.setState(new BrightState);
    delete this;
}

void MediumState::offPressed(LightSwitch& ls)
{
    std::cout << "Light is turned off \n";
    ls.setState(new OffState);
    delete this;
}

void OffState::onPressed(LightSwitch& ls)
{
    std::cout << "Light is turned on but dimmed \n";
    ls.setState(new DimmedState);
    delete this;
}

void OffState::offPressed(LightSwitch& ls)
{
    std::cout << "Light is already turned off \n";
}

void DimmedState::onPressed(LightSwitch& ls)
{
    std::cout << "Brightness of light is increased to medium \n";
    ls.setState(new MediumState);
    delete this;
}

void DimmedState::offPressed(LightSwitch& ls)
{
    std::cout << "Light is turned off \n";
    ls.setState(new OffState);
    delete this; 
}

int main()
{
    LightSwitch ls;
    ls.pressOn();
    ls.pressOn();
    ls.pressOn();
    ls.pressOn();
    ls.pressOff();
    ls.pressOn();
}