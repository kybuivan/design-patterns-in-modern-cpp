#include <iostream>
#include <memory>

// Abstract Products
class Processor
{
public:
    virtual void info() = 0;
};

class Screen
{
public:
    virtual void info() = 0;
};

class Battery
{
public:
    virtual void info() = 0;
};

// Concrete Products
class IntelProcessor : public Processor
{
public:
    void info() override
    {
        std::cout << "Intel Processor" << std::endl;
    }
};

// Concrete Products
class SnapdragonProcessor : public Processor
{
public:
    void info() override
    {
        std::cout << "Snapdragon Processor" << std::endl;
    }
};

class AMDScreen : public Screen
{
public:
    void info() override
    {
        std::cout << "AMD Screen" << std::endl;
    }
};

class SamsungBattery : public Battery
{
public:
    void info() override
    {
        std::cout << "Samsung Battery" << std::endl;
    }
};

// Abstract Factory
class DeviceFactory
{
public:
    virtual std::shared_ptr<Processor> createProcessor() = 0;
    virtual std::shared_ptr<Screen> createScreen() = 0;
    virtual std::shared_ptr<Battery> createBattery() = 0;
};

// Concrete Factories
class LaptopFactory : public DeviceFactory
{
public:
    std::shared_ptr<Processor> createProcessor() override
    {
        return std::make_shared<IntelProcessor>();
    }
    std::shared_ptr<Screen> createScreen() override
    {
        return std::make_shared<AMDScreen>();
    }
    std::shared_ptr<Battery> createBattery() override
    {
        return std::make_shared<SamsungBattery>();
    }
};

class SmartphoneFactory : public DeviceFactory
{
public:
    std::shared_ptr<Processor> createProcessor() override
    {
        return std::make_shared<SnapdragonProcessor>();
    }
    std::shared_ptr<Screen> createScreen() override
    {
        return std::make_shared<AMDScreen>();
    }
    std::shared_ptr<Battery> createBattery() override
    {
        return std::make_shared<SamsungBattery>();
    }
};

// Client
class Device
{
public:
    Device(std::shared_ptr<DeviceFactory> factory)
    {
        processor = factory->createProcessor();
        screen = factory->createScreen();
        battery = factory->createBattery();
    }

    void info()
    {
        std::cout << "Device components:" << std::endl;
        processor->info();
        screen->info();
        battery->info();
    }

private:
    std::shared_ptr<Processor> processor;
    std::shared_ptr<Screen> screen;
    std::shared_ptr<Battery> battery;
};

int main()
{
    std::shared_ptr<DeviceFactory> laptopFactory = std::make_shared<LaptopFactory>();
    std::shared_ptr<DeviceFactory> smartphoneFactory = std::make_shared<SmartphoneFactory>();

    Device laptop(laptopFactory);
    Device smartphone(smartphoneFactory);

    std::cout << "Laptop details:" << std::endl;
    laptop.info();

    std::cout << "\nSmartphone details:" << std::endl;
    smartphone.info();

    return 0;
}
