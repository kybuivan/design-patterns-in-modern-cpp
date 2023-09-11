#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Subject;

class Observer
{
public:
    virtual ~Observer() = default;

    virtual void update(Subject &subject) = 0;
};

class Subject
{
    std::vector<std::weak_ptr<Observer>> observers;
    std::string state;

public:
    void attach(std::shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer)
    {
        for (auto it = observers.begin(); it != observers.end(); it++)
        {
            if (auto sp = it->lock(); sp && sp.get() == observer.get())
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
            if (auto sp = observer.lock())
            {
                sp->update(*this);
            }
        }
    }

    void setState(std::string state)
    {
        this->state = state;
        notify();
    }

    std::string getState() const
    {
        return state;
    }
};

class Textbox : public Observer
{
    std::string name;

public:
    Textbox(std::string name)
    {
        this->name = name;
    }

    void update(Subject &subject) override
    {
        std::cout << name << " updated with new state: " << subject.getState() << std::endl;
    }
};

int main()
{
    Subject subject;
    auto textbox1 = std::make_shared<Textbox>("Textbox 1");
    auto textbox2 = std::make_shared<Textbox>("Textbox 2");
    subject.attach(textbox1);
    subject.attach(textbox2);
    subject.setState("New state");

    subject.detach(textbox1);
    subject.setState("Another state");

    return 0;
}
