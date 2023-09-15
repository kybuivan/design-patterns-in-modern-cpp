#include <iostream>
#include <memory>

// Component interface representing a character
class Character
{
public:
    virtual void display() = 0;
    virtual ~Character() = default;
};

// Concrete implementation of Character
class BaseCharacter : public Character
{
public:
    void display() override
    {
        std::cout << "Character" << std::endl;
    }
};

// Decorator interface
class CharacterDecorator : public Character
{
protected:
    std::shared_ptr<Character> character;

public:
    CharacterDecorator(std::shared_ptr<Character> character) : character(character)
    {
    }
    void display() override
    {
        character->display();
    }
};

// Concrete decorator representing a weapon
class WeaponDecorator : public CharacterDecorator
{
private:
    std::string weaponName;

public:
    WeaponDecorator(std::shared_ptr<Character> character, const std::string &weaponName)
        : CharacterDecorator(character), weaponName(weaponName)
    {
    }

    void display() override
    {
        CharacterDecorator::display();
        std::cout << "Weapon: " << weaponName << std::endl;
    }
};

int main()
{
    // Create a base character
    std::shared_ptr<Character> character = std::make_shared<BaseCharacter>();

    // Decorate the character with a weapon
    std::shared_ptr<Character> characterWithWeapon = std::make_shared<WeaponDecorator>(character, "Sword");

    // Decorate the character with another weapon
    std::shared_ptr<Character> characterWithTwoWeapons =
        std::make_shared<WeaponDecorator>(characterWithWeapon, "Shield");

    // Display the character with weapons
    characterWithTwoWeapons->display();

    return 0;
}
