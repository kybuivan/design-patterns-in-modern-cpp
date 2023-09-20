#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Abstract Product: Pizza
class Pizza
{
public:
    virtual std::string GetName() const = 0;
    virtual void Prepare() = 0;
    virtual void Bake() = 0;
    virtual void Cut() = 0;
    virtual void Box() = 0;
};

// Concrete Product: RomanPizza
class RomanPizza : public Pizza
{
public:
    std::string GetName() const override
    {
        return "Roman Pizza";
    }

    void Prepare() override
    {
        std::cout << "Preparing Roman pizza." << std::endl;
    }

    void Bake() override
    {
        std::cout << "Baking Roman pizza." << std::endl;
    }

    void Cut() override
    {
        std::cout << "Cutting Roman pizza." << std::endl;
    }

    void Box() override
    {
        std::cout << "Boxing Roman pizza." << std::endl;
    }
};

// Concrete Product: MilanesePizza
class MilanesePizza : public Pizza
{
public:
    std::string GetName() const override
    {
        return "Milanese Pizza";
    }

    void Prepare() override
    {
        std::cout << "Preparing Milanese pizza." << std::endl;
    }

    void Bake() override
    {
        std::cout << "Baking Milanese pizza." << std::endl;
    }

    void Cut() override
    {
        std::cout << "Cutting Milanese pizza." << std::endl;
    }

    void Box() override
    {
        std::cout << "Boxing Milanese pizza." << std::endl;
    }
};

// Abstract Factory: AbstractPizzaFactory
class AbstractPizzaFactory
{
public:
    virtual std::shared_ptr<Pizza> CreatePizza() = 0;
};

// Concrete Factory: RomanPizzaFactory
class RomanPizzaFactory : public AbstractPizzaFactory
{
public:
    std::shared_ptr<Pizza> CreatePizza() override
    {
        return std::make_shared<RomanPizza>();
    }
};

// Concrete Factory: MilanesePizzaFactory
class MilanesePizzaFactory : public AbstractPizzaFactory
{
public:
    std::shared_ptr<Pizza> CreatePizza() override
    {
        return std::make_shared<MilanesePizza>();
    }
};

int main()
{
    // Create a Roman pizza using RomanPizzaFactory
    std::shared_ptr<AbstractPizzaFactory> romanFactory = std::make_shared<RomanPizzaFactory>();
    std::shared_ptr<Pizza> romanPizza = romanFactory->CreatePizza();

    // Create a Milanese pizza using MilanesePizzaFactory
    std::shared_ptr<AbstractPizzaFactory> milaneseFactory = std::make_shared<MilanesePizzaFactory>();
    std::shared_ptr<Pizza> milanesePizza = milaneseFactory->CreatePizza();

    // Prepare, bake, cut, and box the pizzas
    romanPizza->Prepare();
    romanPizza->Bake();
    romanPizza->Cut();
    romanPizza->Box();

    milanesePizza->Prepare();
    milanesePizza->Bake();
    milanesePizza->Cut();
    milanesePizza->Box();

    return 0;
}
