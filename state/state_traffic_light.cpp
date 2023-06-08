#include <iostream>
using namespace std;

class State
{
public:
    virtual void signal() = 0;
};

class Red : public State
{
public:
    void signal()
    {
        cout << "Stop" << endl;
    }
};

class Yellow : public State
{
public:
    void signal()
    {
        cout << "Slow down" << endl;
    }
};

class Green : public State
{
public:
    void signal()
    {
        cout << "Go" << endl;
    }
};

class TrafficLight
{
private:
    State *currentState;

public:
    TrafficLight()
    {
        currentState = new Red;
    }

    void changeState(State *state)
    {
        currentState = state;
    }

    void signal()
    {
        currentState->signal();
    }
};

int main()
{
    TrafficLight *trafficLight = new TrafficLight;

    trafficLight->signal();
    trafficLight->changeState(new Green);
    trafficLight->signal();
    trafficLight->changeState(new Yellow);
    trafficLight->signal();

    delete trafficLight;

    return 0;
}
