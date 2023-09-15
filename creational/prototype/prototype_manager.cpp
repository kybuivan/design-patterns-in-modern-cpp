#include <iostream>
#include <memory>
#include <unordered_map>

// Abstract base class for game characters
class Character
{
public:
    virtual std::shared_ptr<Character> clone() const = 0;
    virtual void render() const = 0;
    virtual ~Character() = default;
};

// Concrete class for a specific game character
class Warrior : public Character
{
public:
    std::shared_ptr<Character> clone() const override
    {
        return std::make_shared<Warrior>(*this);
    }

    void render() const override
    {
        std::cout << "Warrior character is rendered." << std::endl;
    }
};

class Mage : public Character
{
public:
    std::shared_ptr<Character> clone() const override
    {
        return std::make_shared<Mage>(*this);
    }

    void render() const override
    {
        std::cout << "Mage character is rendered." << std::endl;
    }
};

class Archer : public Character
{
public:
    std::shared_ptr<Character> clone() const override
    {
        return std::make_shared<Archer>(*this);
    }

    void render() const override
    {
        std::cout << "Archer character is rendered." << std::endl;
    }
};

// PrototypeManager to manage character prototypes
class PrototypeManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<Character>> prototypes;

public:
    PrototypeManager()
    {
        // Initialize prototypes
        prototypes["Warrior"] = std::make_shared<Warrior>();
        prototypes["Mage"] = std::make_shared<Mage>();
        prototypes["Archer"] = std::make_shared<Archer>();
    }

    std::shared_ptr<Character> getPrototype(const std::string &type)
    {
        if (prototypes.find(type) != prototypes.end())
        {
            return prototypes[type]->clone();
        }
        return nullptr;
    }
};

int main()
{
    PrototypeManager manager;

    // Create characters using prototypes
    auto warrior1 = manager.getPrototype("Warrior");
    auto mage1 = manager.getPrototype("Mage");
    auto archer1 = manager.getPrototype("Archer");

    // Render characters
    warrior1->render();
    mage1->render();
    archer1->render();

    return 0;
}
