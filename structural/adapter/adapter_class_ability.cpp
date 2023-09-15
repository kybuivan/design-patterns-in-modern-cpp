#include <iostream>
#include <memory>

// Target interface for character abilities
class Ability
{
public:
    virtual void useAbility() = 0;
    virtual ~Ability() = default;
};

// Adaptee 1: FireAbility class
class FireAbility
{
public:
    void activateFire()
    {
        std::cout << "Activating fire ability." << std::endl;
    }
};

// Adaptee 2: IceAbility class
class IceAbility
{
public:
    void activateIce()
    {
        std::cout << "Activating ice ability." << std::endl;
    }
};

// Class Adapter to adapt FireAbility and IceAbility to the Ability interface
class AbilityAdapter : public Ability, private FireAbility, private IceAbility
{
public:
    void useAbility() override
    {
        // Choose which ability to use based on the situation
        if (isFireMode)
        {
            activateFire();
        }
        else
        {
            activateIce();
        }
    }

    void toggleMode()
    {
        isFireMode = !isFireMode;
    }

private:
    bool isFireMode = true;
};

// Character class that can use abilities
class Character
{
public:
    Character(std::shared_ptr<Ability> ability) : ability_(ability)
    {
    }

    void performAbility()
    {
        std::cout << "Character is ready to use the ability." << std::endl;
        ability_->useAbility();
    }

private:
    std::shared_ptr<Ability> ability_;
};

int main()
{
    // Create AbilityAdapter instance to adapt FireAbility and IceAbility
    auto abilityAdapter = std::make_shared<AbilityAdapter>();

    // Create characters with different abilities
    Character fireCharacter(abilityAdapter);
    Character iceCharacter(abilityAdapter);

    // Perform abilities
    fireCharacter.performAbility();
    iceCharacter.performAbility();

    // Toggle the ability mode
    abilityAdapter->toggleMode();
    fireCharacter.performAbility();
    iceCharacter.performAbility();

    return 0;
}
