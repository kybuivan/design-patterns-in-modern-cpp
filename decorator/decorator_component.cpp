#include <iostream>
#include <string>

class Component
{
public:
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
    Milk(Component *component) : component_(component)
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
    Component *component_;
};

class Sugar : public CondimentDecorator
{
public:
    Sugar(Component *component) : component_(component)
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
    Component *component_;
};

int main()
{
    Beverage coffee("Coffee", 2.0);
    Milk milk(&coffee);
    Sugar sugar(&milk);
    std::cout << sugar.GetDescription() << " costs $" << sugar.GetCost() << std::endl;
    return 0;
}
