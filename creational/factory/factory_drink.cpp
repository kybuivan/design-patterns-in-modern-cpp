#include <functional>
#include <iostream>
#include <map>
#include <memory>

class Drink
{
public:
    virtual ~Drink() = default;
    virtual std::string name() const = 0;
};

class Coffee : public Drink
{
public:
    std::string name() const override
    {
        return "Coffee";
    }
};

class Tea : public Drink
{
public:
    std::string name() const override
    {
        return "Tea";
    }
};

class Juice : public Drink
{
public:
    std::string name() const override
    {
        return "Juice";
    }
};

using DrinkFactory = std::function<std::unique_ptr<Drink>()>;
std::map<std::string, DrinkFactory> drink_factories;

void register_drink(const std::string &name, DrinkFactory factory)
{
    drink_factories[name] = factory;
}

int main()
{
    register_drink("Coffee", [] { return std::make_unique<Coffee>(); });
    register_drink("Tea", [] { return std::make_unique<Tea>(); });
    register_drink("Juice", [] { return std::make_unique<Juice>(); });

    std::string drink_name = "Tea"; // fix build in action
    std::cout << "Enter drink name: ";
    //std::cin >> drink_name;

    auto factory = drink_factories[drink_name];
    if (!factory)
    {
        std::cerr << "Unknown drink" << std::endl;
        return 1;
    }

    auto drink = factory();
    std::cout << "Made a " << drink->name() << std::endl;

    return 0;
}
