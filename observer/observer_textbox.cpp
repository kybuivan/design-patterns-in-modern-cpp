#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Subject;

class Observer
{
public:
    virtual void update(Subject *subject) = 0;
};

class Subject
{
    vector<Observer *> observers;
    string state;

public:
    void attach(Observer *observer)
    {
        observers.push_back(observer);
    }

    void detach(Observer *observer)
    {
        for (auto it = observers.begin(); it != observers.end(); it++)
        {
            if (*it == observer)
            {
                observers.erase(it);
                break;
            }
        }
    }

    void notify()
    {
        for (auto observer : observers)
        {
            observer->update(this);
        }
    }

    void setState(string state)
    {
        this->state = state;
        notify();
    }

    string getState() const
    {
        return state;
    }
};

class Textbox : public Observer
{
    string name;

public:
    Textbox(string name)
    {
        this->name = name;
    }

    void update(Subject *subject) override
    {
        cout << name << " updated with new state: " << subject->getState() << endl;
    }
};

int main()
{
    Subject subject;
    Textbox textbox1("Textbox 1");
    Textbox textbox2("Textbox 2");
    subject.attach(&textbox1);
    subject.attach(&textbox2);
    subject.setState("New state");

    subject.detach(&textbox1);
    subject.setState("Another state");

    return 0;
}
