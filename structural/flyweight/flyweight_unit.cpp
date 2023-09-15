#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Flyweight interface representing common properties of game units.
class Unit
{
public:
    virtual void render(int x, int y) = 0;
};

// Concrete Flyweight representing a specific type of unit.
class Soldier : public Unit
{
public:
    std::string name;
    std::string weapon;

public:
    Soldier(const std::string &name, const std::string &weapon) : name(name), weapon(weapon)
    {
    }

    void render(int x, int y) override
    {
        std::cout << "Soldier " << name << " with " << weapon << " at position (" << x << ", " << y << ")" << std::endl;
    }
};

// Flyweight Factory manages creation and retrieval of Flyweight units.
class UnitFactory
{
private:
    std::vector<std::shared_ptr<Unit>> units;

public:
    std::shared_ptr<Unit> getUnit(const std::string &name, const std::string &weapon)
    {
        // Check if the unit with the given name already exists.
        for (const auto &unit : units)
        {
            if (unit->render(0, 0),
                dynamic_cast<Soldier *>(unit.get())->name == name &&
                    dynamic_cast<Soldier *>(unit.get())->weapon == weapon)
            {
                return unit;
            }
        }

        // If not, create a new unit and add it to the collection.
        auto newUnit = std::make_shared<Soldier>(name, weapon);
        units.push_back(newUnit);
        return newUnit;
    }
};

int main()
{
    // Create a UnitFactory to manage Flyweight units.
    UnitFactory unitFactory;

    // Create different soldiers (Flyweights).
    auto soldier1 = unitFactory.getUnit("John", "Rifle");
    auto soldier2 = unitFactory.getUnit("Alice", "Machine Gun");
    auto soldier3 = unitFactory.getUnit("John", "Rifle"); // Reusing the "John" Rifle soldier.

    // Simulate a game scenario.
    std::vector<std::shared_ptr<Unit>> gameUnits = {soldier1, soldier2, soldier3};

    // Render the game units.
    for (int i = 0; i < gameUnits.size(); ++i)
    {
        gameUnits[i]->render(i * 10, 20);
    }

    return 0;
}
