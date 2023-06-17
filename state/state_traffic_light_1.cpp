#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// Forward declaration of the TrafficLight class
class TrafficLight;

// Abstract base class for traffic light states
class TrafficLightState
{
public:
    virtual ~TrafficLightState() = default;

    virtual void update(TrafficLight &trafficLight) = 0;
};

// Concrete state class for the "Green" state
class GreenLightState : public TrafficLightState
{
public:
    void update(TrafficLight &trafficLight) override;
};

// Concrete state class for the "Red" state
class RedLightState : public TrafficLightState
{
public:
    void update(TrafficLight &trafficLight) override;
};

// Concrete state class for the "Yellow" state
class YellowLightState : public TrafficLightState
{
public:
    void update(TrafficLight &trafficLight) override;
};

// Traffic light class that uses the State pattern
class TrafficLight
{
public:
    TrafficLight()
    {
        m_state = std::make_unique<RedLightState>();
    }

    void setState(std::unique_ptr<TrafficLightState> state)
    {
        m_state = std::move(state);
    }

    void update()
    {
        m_state->update(*this);
    }

private:
    std::unique_ptr<TrafficLightState> m_state;
};

void RedLightState::update(TrafficLight &trafficLight)
{
    std::cout << "Red light is on. Changing to green in 1 second." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    trafficLight.setState(std::make_unique<GreenLightState>());
}

void YellowLightState::update(TrafficLight &trafficLight)
{
    std::cout << "Yellow light is on. Changing to red in 1 second." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    trafficLight.setState(std::make_unique<RedLightState>());
}

void GreenLightState::update(TrafficLight &trafficLight)
{
    std::cout << "Green light is on. Changing to yellow in 1 second." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    trafficLight.setState(std::make_unique<YellowLightState>());
}

// Main program
int main()
{
    TrafficLight trafficLight;

    for (int i = 0; i < 5; ++i)
    {
        trafficLight.update();
    }

    return 0;
}
