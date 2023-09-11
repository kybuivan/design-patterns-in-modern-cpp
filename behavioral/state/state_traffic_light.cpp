#include <iostream>
#include <memory>

class State
{
public:
    virtual ~State() = default;

    virtual void signal() = 0;
};

class Red : public State
{
public:
    void signal() override
    {
        std::cout << "Stop" << std::endl;
    }
};

class Yellow : public State
{
public:
    void signal() override
    {
        std::cout << "Slow down" << std::endl;
    }
};

class Green : public State
{
public:
    void signal() override
    {
        std::cout << "Go" << std::endl;
    }
};

class TrafficLight
{
private:
    std::unique_ptr<State> currentState;

public:
    TrafficLight()
    {
        currentState = std::make_unique<Red>();
    }

    void changeState(std::unique_ptr<State> state)
    {
        currentState = std::move(state);
    }

    void signal()
    {
        currentState->signal();
    }
};

int main()
{
    std::unique_ptr<TrafficLight> trafficLight = std::make_unique<TrafficLight>();

    trafficLight->signal();
    trafficLight->changeState(std::make_unique<Green>());
    trafficLight->signal();
    trafficLight->changeState(std::make_unique<Yellow>());
    trafficLight->signal();

    return 0;
}
