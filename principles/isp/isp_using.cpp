#include <iostream>

// ISP-compliant interfaces

// Interface for a device that can be turned on and off
class Switchable
{
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

// Interface for a device that can be dimmed
class Dimmable
{
public:
    virtual void setBrightness(int level) = 0;
};

// Concrete implementation: LightBulb that is both switchable and dimmable
class LightBulb : public Switchable, public Dimmable
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

    void setBrightness(int level) override
    {
        std::cout << "LightBulb brightness set to " << level << std::endl;
    }
};

int main()
{
    LightBulb bulb;

    bulb.turnOn();
    bulb.setBrightness(50);
    bulb.turnOff();

    return 0;
}
