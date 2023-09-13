#include <iostream>
#include <memory>

// Abstract Product: Weapon
class Weapon
{
public:
    virtual void display() = 0;
};

// Concrete Products: Sword and Staff
class Sword : public Weapon
{
public:
    void display() override
    {
        std::cout << "Sword" << std::endl;
    }
};

class Staff : public Weapon
{
public:
    void display() override
    {
        std::cout << "Staff" << std::endl;
    }
};

// Abstract Product: Armor
class Armor
{
public:
    virtual void display() = 0;
};

// Concrete Products: PlateArmor and Robe
class PlateArmor : public Armor
{
public:
    void display() override
    {
        std::cout << "Plate Armor" << std::endl;
    }
};

class Robe : public Armor
{
public:
    void display() override
    {
        std::cout << "Robe" << std::endl;
    }
};

// Abstract Product: Character
class Character
{
public:
    Character(std::shared_ptr<Weapon> weapon, std::shared_ptr<Armor> armor) : weapon(weapon), armor(armor)
    {
    }
    virtual void display() = 0;

protected:
    std::shared_ptr<Weapon> weapon;
    std::shared_ptr<Armor> armor;
};

// Concrete Products: Warrior and Mage
class Warrior : public Character
{
public:
    Warrior(std::shared_ptr<Weapon> weapon, std::shared_ptr<Armor> armor) : Character(weapon, armor)
    {
    }
    void display() override
    {
        std::cout << "Warrior with ";
        weapon->display();
        armor->display();
    }
};

class Mage : public Character
{
public:
    Mage(std::shared_ptr<Weapon> weapon, std::shared_ptr<Armor> armor) : Character(weapon, armor)
    {
    }
    void display() override
    {
        std::cout << "Mage with ";
        weapon->display();
        armor->display();
    }
};

// Abstract Factory
class CharacterFactory
{
public:
    virtual std::shared_ptr<Warrior> createWarrior() = 0;
    virtual std::shared_ptr<Mage> createMage() = 0;
};

// Concrete Factories: KnightFactory and WizardFactory
class KnightFactory : public CharacterFactory
{
public:
    std::shared_ptr<Warrior> createWarrior() override
    {
        return std::make_shared<Warrior>(std::make_shared<Sword>(), std::make_shared<PlateArmor>());
    }
    std::shared_ptr<Mage> createMage() override
    {
        return std::make_shared<Mage>(std::make_shared<Staff>(), std::make_shared<Robe>());
    }
};

class WizardFactory : public CharacterFactory
{
public:
    std::shared_ptr<Warrior> createWarrior() override
    {
        return std::make_shared<Warrior>(std::make_shared<Sword>(), std::make_shared<Robe>());
    }
    std::shared_ptr<Mage> createMage() override
    {
        return std::make_shared<Mage>(std::make_shared<Staff>(), std::make_shared<Robe>());
    }
};

int main()
{
    std::shared_ptr<CharacterFactory> knightFactory = std::make_shared<KnightFactory>();
    std::shared_ptr<CharacterFactory> wizardFactory = std::make_shared<WizardFactory>();

    std::shared_ptr<Warrior> knight = knightFactory->createWarrior();
    std::shared_ptr<Mage> wizard = wizardFactory->createMage();

    knight->display();
    wizard->display();

    return 0;
}
