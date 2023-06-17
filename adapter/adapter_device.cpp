#include <iostream>
#include <memory>
#include <vector>

// The interface for the devices that need to be adapted
class Device
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Device() = default;
};

// The concrete device that needs to be adapted
class OlderDevice : public Device
{
public:
    void start() override
    {
        std::cout << "Older device started." << std::endl;
    }

    void stop() override
    {
        std::cout << "Older device stopped." << std::endl;
    }
};

// The interface for the systems that require the adapted device
class NewSystem
{
public:
    virtual void startDevice() = 0;
    virtual void stopDevice() = 0;
    virtual ~NewSystem()
    {
    }
};

// The adapter class that implements the NewSystem interface and adapts the OlderDevice
class NewSystemAdapter : public NewSystem
{
public:
    explicit NewSystemAdapter(std::shared_ptr<Device> device) : device_(device)
    {
    }

    void startDevice() override
    {
        device_->start();
    }

    void stopDevice() override
    {
        device_->stop();
    }

private:
    std::shared_ptr<Device> device_;
};

int main()
{
    // Create the OlderDevice instance using a shared pointer
    std::shared_ptr<Device> olderDevice = std::make_shared<OlderDevice>();

    // Create the NewSystemAdapter instance and pass the OlderDevice shared pointer to it
    std::shared_ptr<NewSystem> adapter = std::make_shared<NewSystemAdapter>(olderDevice);

    // Use the adapter to start and stop the OlderDevice
    adapter->startDevice();
    adapter->stopDevice();

    return 0;
}
