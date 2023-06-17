#include <iostream>
#include <map>
#include <memory>
#include <string>

// Abstract class for button prototypes
class ButtonPrototype
{
public:
    virtual std::unique_ptr<ButtonPrototype> clone() = 0;
    virtual void draw() = 0;
};

// Concrete prototypes for button objects
class RoundButton : public ButtonPrototype
{
public:
    std::unique_ptr<ButtonPrototype> clone() override
    {
        return std::make_unique<RoundButton>(*this);
    }

    void draw() override
    {
        std::cout << "Drawing a round button" << std::endl;
    }
};

class SquareButton : public ButtonPrototype
{
public:
    std::unique_ptr<ButtonPrototype> clone() override
    {
        return std::make_unique<SquareButton>(*this);
    }

    void draw() override
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
        prototypes_["Round"] = std::make_unique<RoundButton>();
        prototypes_["Square"] = std::make_unique<SquareButton>();
    }

    std::unique_ptr<ButtonPrototype> create(const std::string &type)
    {
        return prototypes_[type]->clone();
    }

private:
    std::map<std::string, std::unique_ptr<ButtonPrototype>> prototypes_;
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
    std::unique_ptr<ButtonPrototype> button1_;
    std::unique_ptr<ButtonPrototype> button2_;
};

int main()
{
    ButtonRegistry registry;
    Client client(registry);
    client.drawButtons();

    return 0;
}
