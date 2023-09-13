#include <iostream>

// A single, large interface for a multifunctional device
class MultiFunctionalDevice
{
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setBrightness(int level) = 0;
    virtual void print() = 0;
    virtual void scan() = 0;
};

// Concrete implementation: Printer that implements the large interface
class Printer : public MultiFunctionalDevice
{
public:
    void turnOn() override
    {
        std::cout << "Printer is ON" << std::endl;
    }

    void turnOff() override
    {
        std::cout << "Printer is OFF" << std::endl;
    }

    void setBrightness(int level) override
    {
        std::cout << "Printer does not have brightness control." << std::endl;
    }

    void print() override
    {
        std::cout << "Printing..." << std::endl;
    }

    void scan() override
    {
        std::cout << "Scanning..." << std::endl;
    }
};

int main()
{
    Printer printer;

    printer.turnOn();
    printer.print();
    printer.turnOff();

    return 0;
}
