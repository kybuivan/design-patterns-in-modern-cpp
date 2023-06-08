#include <iostream>
#include <vector>

// The interface for the devices that need to be adapted
class Device
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
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
};

// The adapter class that implements the NewSystem interface and adapts the OlderDevice
class NewSystemAdapter : public NewSystem
{
public:
    explicit NewSystemAdapter(Device *device) : device_{device}
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
    Device *device_;
};

int main()
{
    // Create the OlderDevice instance
    OlderDevice olderDevice;

    // Create the NewSystemAdapter instance and pass the OlderDevice instance to it
    NewSystemAdapter adapter{&olderDevice};

    // Use the adapter to start and stop the OlderDevice
    adapter.startDevice();
    adapter.stopDevice();

    return 0;
}
