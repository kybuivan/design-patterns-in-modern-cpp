#include <iostream>

// Abstraction representing a Device
class Device
{
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

// Concrete implementation: LightBulb
class LightBulb : public Device
{
public:
    void turnOn() override
    {
        std::cout << "LightBulb is ON" << std::endl;
    }

    void turnOff() override
    {
        std::cout << "LightBulb is OFF" << std::endl;
    }
};

// Concrete implementation: Fan
class Fan : public Device
{
public:
    void turnOn() override
    {
        std::cout << "Fan is ON" << std::endl;
    }

    void turnOff() override
    {
        std::cout << "Fan is OFF" << std::endl;
    }
};

// Abstraction representing a Switch
class Switch
{
public:
    virtual void control(Device &device) = 0;
};

// Concrete implementation: ButtonSwitch
class ButtonSwitch : public Switch
{
public:
    void control(Device &device) override
    {
        // This demonstrates the Dependency Inversion Principle.
        // The Switch depends on an abstraction (Device) rather than a concrete implementation.
        device.turnOn();
        device.turnOff();
    }
};

int main()
{
    LightBulb bulb;
    Fan fan;
    ButtonSwitch button;

    // The Switch is controlling both the LightBulb and the Fan,
    // without knowing their specific implementations.
    button.control(bulb);
    button.control(fan);

    return 0;
}
