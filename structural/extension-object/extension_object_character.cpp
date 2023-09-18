#include <iostream>
#include <memory>
#include <string>

// Abstract interface for character abilities
class CharacterAbility
{
public:
    virtual void useAbility() = 0;
};

// Concrete implementation of a basic attack ability
class BasicAttack : public CharacterAbility
{
public:
    void useAbility() override
    {
        std::cout << "Basic Attack" << std::endl;
    }
};

// Concrete implementation of a special ability (e.g., fireball)
class SpecialAbility : public CharacterAbility
{
public:
    void useAbility() override
    {
        std::cout << "Special Ability: Fireball" << std::endl;
    }
};

// Game character class with the ability to equip abilities
class GameCharacter
{
private:
    std::shared_ptr<CharacterAbility> ability;

public:
    void equipAbility(std::shared_ptr<CharacterAbility> a)
    {
        ability = a;
    }

    void useEquippedAbility()
    {
        if (ability)
        {
            ability->useAbility();
        }
        else
        {
            std::cout << "No ability equipped" << std::endl;
        }
    }
};

int main()
{
    GameCharacter character;

    // Character starts with a basic attack ability
    std::shared_ptr<CharacterAbility> basicAttack = std::make_shared<BasicAttack>();
    character.equipAbility(basicAttack);

    // Use the equipped ability (basic attack)
    character.useEquippedAbility();

    // Switch to a special ability
    std::shared_ptr<CharacterAbility> specialAbility = std::make_shared<SpecialAbility>();
    character.equipAbility(specialAbility);

    // Use the equipped ability (special ability)
    character.useEquippedAbility();

    return 0;
}
