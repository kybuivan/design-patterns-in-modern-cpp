#include <iostream>
#include <memory>

// Target interface for weapons
class Weapon
{
public:
    virtual void attack() = 0;
    virtual ~Weapon() = default;
};

// Adaptee 1: Sword class
class Sword
{
public:
    void swingSword()
    {
        std::cout << "Swinging a sword." << std::endl;
    }
};

// Adaptee 2: Gun class
class Gun
{
public:
    void shootGun()
    {
        std::cout << "Shooting a gun." << std::endl;
    }
};

// Object Adapter to adapt Sword and Gun to the Weapon interface
class WeaponAdapter : public Weapon
{
public:
    WeaponAdapter(std::shared_ptr<Sword> sword) : sword_(sword)
    {
    }
    WeaponAdapter(std::shared_ptr<Gun> gun) : gun_(gun)
    {
    }

    void attack() override
    {
        if (sword_)
        {
            sword_->swingSword();
        }
        else if (gun_)
        {
            gun_->shootGun();
        }
    }

private:
    std::shared_ptr<Sword> sword_;
    std::shared_ptr<Gun> gun_;
};

// Character class that can use weapons
class Character
{
public:
    Character(std::shared_ptr<Weapon> weapon) : weapon_(weapon)
    {
    }

    void performAttack()
    {
        std::cout << "Character is ready to attack." << std::endl;
        weapon_->attack();
    }

private:
    std::shared_ptr<Weapon> weapon_;
};

int main()
{
    // Create Sword and Gun objects
    auto sword = std::make_shared<Sword>();
    auto gun = std::make_shared<Gun>();

    // Create WeaponAdapter instances to adapt Sword and Gun
    auto swordAdapter = std::make_shared<WeaponAdapter>(sword);
    auto gunAdapter = std::make_shared<WeaponAdapter>(gun);

    // Create characters with different weapons
    Character swordCharacter(swordAdapter);
    Character gunCharacter(gunAdapter);

    // Perform attacks
    swordCharacter.performAttack();
    gunCharacter.performAttack();

    return 0;
}
