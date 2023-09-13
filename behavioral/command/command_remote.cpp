#include <iostream>
#include <memory>
#include <vector>

// Receiver: Electronic Device
class ElectronicDevice
{
public:
    virtual void on() = 0;
    virtual void off() = 0;
};

// Concrete Receivers: Television and Stereo
class Television : public ElectronicDevice
{
public:
    void on() override
    {
        std::cout << "Television is ON" << std::endl;
    }

    void off() override
    {
        std::cout << "Television is OFF" << std::endl;
    }
};

class Stereo : public ElectronicDevice
{
public:
    void on() override
    {
        std::cout << "Stereo is ON" << std::endl;
    }

    void off() override
    {
        std::cout << "Stereo is OFF" << std::endl;
    }
};

// Command: Abstract Command
class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Concrete Commands: TurnOnCommand and TurnOffCommand
class TurnOnCommand : public Command
{
public:
    TurnOnCommand(std::shared_ptr<ElectronicDevice> device) : device(device)
    {
    }

    void execute() override
    {
        device->on();
    }

    void undo() override
    {
        device->off();
    }

private:
    std::shared_ptr<ElectronicDevice> device;
};

class TurnOffCommand : public Command
{
public:
    TurnOffCommand(std::shared_ptr<ElectronicDevice> device) : device(device)
    {
    }

    void execute() override
    {
        device->off();
    }

    void undo() override
    {
        device->on();
    }

private:
    std::shared_ptr<ElectronicDevice> device;
};

// Invoker: RemoteControl
class RemoteControl
{
public:
    void setCommand(std::shared_ptr<Command> onCommand, std::shared_ptr<Command> offCommand)
    {
        this->onCommand = onCommand;
        this->offCommand = offCommand;
    }

    void pressOnButton()
    {
        onCommand->execute();
        lastCommand = onCommand;
    }

    void pressOffButton()
    {
        offCommand->execute();
        lastCommand = offCommand;
    }

    void pressUndoButton()
    {
        if (lastCommand)
        {
            lastCommand->undo();
            lastCommand = nullptr;
        }
    }

private:
    std::shared_ptr<Command> onCommand;
    std::shared_ptr<Command> offCommand;
    std::shared_ptr<Command> lastCommand;
};

int main()
{
    // Create electronic devices
    std::shared_ptr<ElectronicDevice> television = std::make_shared<Television>();
    std::shared_ptr<ElectronicDevice> stereo = std::make_shared<Stereo>();

    // Create concrete commands
    std::shared_ptr<Command> turnOnTelevision = std::make_shared<TurnOnCommand>(television);
    std::shared_ptr<Command> turnOffTelevision = std::make_shared<TurnOffCommand>(television);
    std::shared_ptr<Command> turnOnStereo = std::make_shared<TurnOnCommand>(stereo);
    std::shared_ptr<Command> turnOffStereo = std::make_shared<TurnOffCommand>(stereo);

    // Create the remote control
    RemoteControl remote;

    // Set the commands for the remote
    remote.setCommand(turnOnTelevision, turnOffTelevision);

    // Use the remote control
    remote.pressOnButton();   // Turns on the television
    remote.pressOffButton();  // Turns off the television
    remote.pressUndoButton(); // Undoes the last command (turns on the television again)

    // Change the commands for the remote
    remote.setCommand(turnOnStereo, turnOffStereo);

    remote.pressOnButton();  // Turns on the stereo
    remote.pressOffButton(); // Turns off the stereo

    return 0;
}
