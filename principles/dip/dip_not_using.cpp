#include <iostream>

// Concrete implementation: LightBulb
class LightBulb
{
public:
    void turnOn()
    {
        std::cout << "LightBulb is ON" << std::endl;
    }

    void turnOff()
    {
        std::cout << "LightBulb is OFF" << std::endl;
    }
};

// Concrete implementation: Fan
class Fan
{
public:
    void turnOn()
    {
        std::cout << "Fan is ON" << std::endl;
    }

    void turnOff()
    {
        std::cout << "Fan is OFF" << std::endl;
    }
};

// Concrete implementation: ButtonSwitch
class ButtonSwitch
{
public:
    void controlLightBulb(LightBulb &bulb)
    {
        // The Switch directly depends on the concrete implementation (LightBulb).
        bulb.turnOn();
        bulb.turnOff();
    }

    void controlFan(Fan &fan)
    {
        // The Switch directly depends on the concrete implementation (Fan).
        fan.turnOn();
        fan.turnOff();
    }
};

int main()
{
    LightBulb bulb;
    Fan fan;
    ButtonSwitch button;

    // The Switch controls the LightBulb and the Fan, but it depends on their specific implementations.
    button.controlLightBulb(bulb);
    button.controlFan(fan);

    return 0;
}
