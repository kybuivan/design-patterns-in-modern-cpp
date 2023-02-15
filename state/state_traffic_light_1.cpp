#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// Forward declaration of the TrafficLight class
class TrafficLight;
// Abstract base class for traffic light states
class TrafficLightState
{
public:
    virtual void update(TrafficLight& trafficLight) = 0;
};

// Traffic light class that uses the State pattern
class TrafficLight
{
public:
    TrafficLight();

    void setState(TrafficLightState* state)
    {
        delete m_state;
        m_state = state;
    }

    void update()
    {
        m_state->update(*this);
    }

private:
    TrafficLightState* m_state;
};
// Concrete state class for the "Green" state

class GreenLightState : public TrafficLightState
{
public:
    void update(TrafficLight& trafficLight) override;
};

// Concrete state class for the "Red" state
class RedLightState : public TrafficLightState
{
public:
    void update(TrafficLight& trafficLight) override;
};

void RedLightState::update(TrafficLight& trafficLight)
{
    std::cout << "Red light is on. Changing to green in 10 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    trafficLight.setState(new GreenLightState());
}

// Concrete state class for the "Yellow" state
class YellowLightState : public TrafficLightState
{
public:
    void update(TrafficLight& trafficLight) override;
};

void YellowLightState::update(TrafficLight& trafficLight)
{
    std::cout << "Yellow light is on. Changing to red in 5 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    trafficLight.setState(new RedLightState());
}

void GreenLightState::update(TrafficLight& trafficLight)
{
    std::cout << "Green light is on. Changing to yellow in 10 seconds." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    trafficLight.setState(new YellowLightState());
}

TrafficLight::TrafficLight()
{
	m_state = new RedLightState();
}

// Main program
int main()
{
    TrafficLight trafficLight;

    for (int i = 0; i < 10; ++i)
    {
        trafficLight.update();
    }

    return 0;
}
