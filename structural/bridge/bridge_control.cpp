#include <iostream>
#include <memory>
#include <string>

// The abstraction defines the interface for the "control" part of the two class
// hierarchies. It maintains a reference to an object of the implementation hierarchy.
class RemoteControl
{
public:
    class TV
    {
    public:
        virtual void on() = 0;
        virtual void off() = 0;
        virtual void tuneChannel(int channel) = 0;
        virtual ~TV() = default;
    };

    std::shared_ptr<TV> tv;

public:
    RemoteControl(std::shared_ptr<TV> tv) : tv(tv)
    {
    }

    void turnOn()
    {
        tv->on();
    }
    void turnOff()
    {
        tv->off();
    }
    void setChannel(int channel)
    {
        tv->tuneChannel(channel);
    }
};

// The RefinedAbstraction extends the interface defined by Abstraction.
class TVRemoteMute : public RemoteControl
{
public:
    TVRemoteMute(std::shared_ptr<TV> tv) : RemoteControl(tv)
    {
    }

    void mute()
    {
        std::cout << "TV was muted" << std::endl;
    }
};

// The implementation defines the interface for the "control" part of the class
// hierarchy. It is used by all concrete implementations.
class Sony : public RemoteControl::TV
{
public:
    void on()
    {
        std::cout << "Sony TV is on" << std::endl;
    }
    void off()
    {
        std::cout << "Sony TV is off" << std::endl;
    }
    void tuneChannel(int channel)
    {
        std::cout << "Sony TV tuned to channel " << channel << std::endl;
    }
};

class Samsung : public RemoteControl::TV
{
public:
    void on()
    {
        std::cout << "Samsung TV is on" << std::endl;
    }
    void off()
    {
        std::cout << "Samsung TV is off" << std::endl;
    }
    void tuneChannel(int channel)
    {
        std::cout << "Samsung TV tuned to channel " << channel << std::endl;
    }
};

int main()
{
    std::shared_ptr<RemoteControl> sonyRemote =
        std::make_shared<TVRemoteMute>(std::make_shared<Sony>());
    std::shared_ptr<RemoteControl> samsungRemote =
        std::make_shared<TVRemoteMute>(std::make_shared<Samsung>());

    sonyRemote->turnOn();
    sonyRemote->setChannel(10);
    sonyRemote->turnOff();

    samsungRemote->turnOn();
    samsungRemote->setChannel(5);
    samsungRemote->turnOff();

    return 0;
}
