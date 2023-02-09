#include <iostream>
#include <map>
#include <string>

// Abstract class for button prototypes
class ButtonPrototype
{
public:
    virtual ButtonPrototype *clone() = 0;
    virtual void draw() = 0;
};

// Concrete prototypes for button objects
class RoundButton : public ButtonPrototype
{
public:
    ButtonPrototype *clone()
    {
        return new RoundButton(*this);
    }

    void draw()
    {
        std::cout << "Drawing a round button" << std::endl;
    }
};

class SquareButton : public ButtonPrototype
{
public:
    ButtonPrototype *clone()
    {
        return new SquareButton(*this);
    }

    void draw()
    {
        std::cout << "Drawing a square button" << std::endl;
    }
};

// Registry for prototypes
class ButtonRegistry
{
public:
    ButtonRegistry()
    {
        prototypes_["Round"] = new RoundButton();
        prototypes_["Square"] = new SquareButton();
    }

    ButtonPrototype *create(const std::string &type)
    {
        return prototypes_[type]->clone();
    }

private:
    std::map<std::string, ButtonPrototype *> prototypes_;
};

// Client
class Client
{
public:
    Client(ButtonRegistry &registry)
    {
        button1_ = registry.create("Round");
        button2_ = registry.create("Square");
    }

    void drawButtons()
    {
        button1_->draw();
        button2_->draw();
    }

private:
    ButtonPrototype *button1_;
    ButtonPrototype *button2_;
};

int main()
{
    ButtonRegistry registry;
    Client client(registry);
    client.drawButtons();

    return 0;
}
