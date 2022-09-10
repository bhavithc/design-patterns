#include <iostream>
#include <array>
#include <memory>

#define MAX_NR_OF_BUTTONS 7

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

class ICommand
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual const char* getClassName() const
    {
        return "ICommand";
    }
};

class LightOnCommand : public ICommand
{
public:
    LightOnCommand(Light& light)
        : m_light(light)
    {

    }

    void execute() override
    {
        m_light.on();
    }

    void undo() override
    {
        m_light.off();
    }

    const char* getClassName() const override
    {
        return "LightOnCommand";
    }

private:
    Light& m_light;
};

class LightOffCommand : public ICommand
{
public:
    LightOffCommand(Light& light)
        : m_light(light)
    {

    }

    void execute() override
    {
        m_light.off();
    }

    void undo() override
    {
        m_light.on();
    }

    const char* getClassName() const override
    {
        return "LightOffCommand";
    }

private:
    Light& m_light;
};

class GarageDoorUpCommand : public ICommand
{
public:
    GarageDoorUpCommand(GarageDoor& garageDoor)
        : m_garageDoor(garageDoor)
    {

    }

    void execute() override
    {
        m_garageDoor.up();
    }

    void undo() override
    {
        m_garageDoor.down();
    }

    const char* getClassName() const override
    {
        return "GarageDoorUpCommand";
    }
private:
    GarageDoor& m_garageDoor;
};

class GarageDoorDownCommand : public ICommand
{
public:
    GarageDoorDownCommand(GarageDoor& garageDoor)
        : m_garageDoor(garageDoor)
    {

    }

    void execute() override
    {
        m_garageDoor.down();
    }

    void undo() override
    {
        m_garageDoor.up();
    }

    const char* getClassName() const override
    {
        return "GarageDoorDownCommand";
    }

private:
    GarageDoor& m_garageDoor;
};

class GarageDoorLightOnCommand : public ICommand
{
public:
    GarageDoorLightOnCommand(GarageDoor& garageDoor)
        : m_garageDoor(garageDoor)
    {

    }

    void execute() override
    {
        m_garageDoor.lightOn();
    }

    void undo() override
    {
        m_garageDoor.lightOff();
    }

    const char* getClassName() const override
    {
        return "GarageDoorLightOnCommand";
    }
private:
    GarageDoor& m_garageDoor;
};

class GarageDoorLightOffCommand : public ICommand
{
public:
    GarageDoorLightOffCommand(GarageDoor& garageDoor)
        : m_garageDoor(garageDoor)
    {

    }

    void execute() override
    {
        m_garageDoor.lightOff();
    }

    void undo() override
    {
        m_garageDoor.lightOn();
    }

    const char* getClassName() const override
    {
        return "GarageDoorLightOffCommand";
    }

private:
    GarageDoor& m_garageDoor;
};

class SterioOnCommand : public ICommand
{
public:
    SterioOnCommand(Sterio& sterio)
        : m_sterio(sterio)
    {

    }

    void execute() override
    {
        m_sterio.on();
    }

    void undo() override
    {
        m_sterio.off();
    }

    const char* getClassName() const override
    {
        return "SterioOnCommand";
    }

private:
    Sterio& m_sterio;
};

class SterioOffCommand : public ICommand
{
public:
    SterioOffCommand(Sterio& sterio)
        : m_sterio(sterio)
    {

    }

    void execute() override
    {
        m_sterio.off();
    }

    void undo() override
    {
        m_sterio.on();
    }

    const char* getClassName() const override
    {
        return "SterioOffCommand";
    }
private:
    Sterio& m_sterio;
};

class SterioVolumeOnCommand : public ICommand
{
public:
    SterioVolumeOnCommand(Sterio& sterio)
        : m_sterio(sterio)
    {

    }

    void execute() override
    {
        m_sterio.setVolume();
    }

    void undo() override
    {
        // see this undo operation is off not volume down
        m_sterio.off();
    }

    const char* getClassName() const override
    {
        return "SterioVolumeOnCommand";
    }

private:
    Sterio& m_sterio;
};

class NoCommand : public ICommand
{
public:
    void execute() override
    {
        std::cout << "No command executed !\n";
    }

    void undo() override
    {
        std::cout << "No command undo executed !\n";
    }

    const char* getClassName() const override
    {
        return "NoCommand";
    }
};

class RemoteControl
{
public:
    RemoteControl()
    {
        for (int i = 0; i < MAX_NR_OF_BUTTONS; i++) {
            m_onCommands[i] = &m_noCommand;
            m_offCommands[i] = &m_noCommand;
        }
        m_undoCommand = &m_noCommand;
    }

    void setCommand(
        int slot, ICommand* pOnCommand, ICommand* pOffCommand)
    {
        if (slot < 0 || slot >= MAX_NR_OF_BUTTONS) {
            std::cerr << "Invalid slot ["<< slot << "] received, unable to set command !\n";
            return;
        }

        m_onCommands[slot] = pOnCommand;
        m_offCommands[slot] = pOffCommand;
    }

    void onButtonPushed(int slot)
    {
        if (slot < 0 || slot >= MAX_NR_OF_BUTTONS) {
            std::cerr << "Invalid slot ["<< slot << "] received, unable to press the button !\n";
            return;
        }

        m_onCommands[slot]->execute();
        // save the command after execute
        m_undoCommand = m_onCommands[slot];
    }

    void offButtonPushed(int slot)
    {
        if (slot < 0 || slot >= MAX_NR_OF_BUTTONS) {
            std::cerr << "Invalid slot ["<< slot << "] received, unable to press the button !\n";
            return;
        }

        m_offCommands[slot]->execute();

        // save the command after execute
        m_undoCommand = m_offCommands[slot];
    }


    // Add undo button pushed
    void undoButtonPushed()
    {
        m_undoCommand->undo();
    }

    friend std::ostream& operator << (std::ostream& os, RemoteControl& rc)
    {
        os << "\n--------------Remote Control----------------\n";
        for (int i = 0; i < MAX_NR_OF_BUTTONS; i++) {
            os  << "[slot " << i << "] " 
                << rc.m_onCommands[i]->getClassName() 
                << " : " 
                << rc.m_offCommands[i]->getClassName() << "\n";
        }
        
        return os;
    }

private:
    std::array<ICommand*, MAX_NR_OF_BUTTONS> m_onCommands = {};
    std::array<ICommand*, MAX_NR_OF_BUTTONS> m_offCommands = {};
    ICommand* m_undoCommand;
    NoCommand m_noCommand;
};

int main()
{
    Light light;
    LightOnCommand ligthOnCommand {light};
    LightOffCommand lightOffCommand {light};

    Sterio sterio;
    SterioOnCommand sterioOnCommand {sterio};
    SterioOffCommand sterioOffCommand {sterio};
    SterioVolumeOnCommand sterioVolumeOnCommand {sterio};

    GarageDoor garageDoor;
    GarageDoorUpCommand garageDoorUpCommand {garageDoor};
    GarageDoorDownCommand garageDoorDownCommand {garageDoor};

    RemoteControl rc;

    rc.setCommand(0, &ligthOnCommand, &lightOffCommand);
    rc.setCommand(1, &garageDoorUpCommand, &garageDoorDownCommand);
    rc.setCommand(2, &sterioOnCommand, &sterioOffCommand);

    rc.onButtonPushed(0);
    rc.offButtonPushed(0);
    rc.undoButtonPushed();

    // second time undo it pressed, but did not happened anything -> Memento solves this
    // rc.undoButtonPushed();

    rc.onButtonPushed(1);
    rc.offButtonPushed(1);
    rc.undoButtonPushed();

    return 0;
}
