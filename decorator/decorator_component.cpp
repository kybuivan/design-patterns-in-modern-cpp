#include <iostream>
#include <memory>
#include <string>

class Component
{
public:
    virtual ~Component() = default;
    virtual std::string GetDescription() const = 0;
    virtual double GetCost() const = 0;
};

class Beverage : public Component
{
public:
    Beverage(std::string description, double cost) : description_(description), cost_(cost)
    {
    }

    std::string GetDescription() const override
    {
        return description_;
    }

    double GetCost() const override
    {
        return cost_;
    }

private:
    std::string description_;
    double cost_;
};

class CondimentDecorator : public Component
{
public:
    virtual std::string GetDescription() const = 0;
};

class Milk : public CondimentDecorator
{
public:
    Milk(std::shared_ptr<Component> component) : component_(component)
    {
    }

    std::string GetDescription() const override
    {
        return component_->GetDescription() + ", Milk";
    }

    double GetCost() const override
    {
        return 0.5 + component_->GetCost();
    }

private:
    std::shared_ptr<Component> component_;
};

class Sugar : public CondimentDecorator
{
public:
    Sugar(std::shared_ptr<Component> component) : component_(component)
    {
    }

    std::string GetDescription() const override
    {
        return component_->GetDescription() + ", Sugar";
    }

    double GetCost() const override
    {
        return 0.3 + component_->GetCost();
    }

private:
    std::shared_ptr<Component> component_;
};

int main()
{
    std::shared_ptr<Beverage> coffee = std::make_shared<Beverage>("Coffee", 2.0);
    std::shared_ptr<Component> milk = std::make_shared<Milk>(coffee);
    std::shared_ptr<Component> sugar = std::make_shared<Sugar>(milk);

    std::cout << sugar->GetDescription() << " costs $" << sugar->GetCost() << std::endl;

    return 0;
}
