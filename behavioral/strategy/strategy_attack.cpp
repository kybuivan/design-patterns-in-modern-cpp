#include <iostream>

// Abstract base class for attack strategies
class AttackStrategy
{
public:
    virtual void attack() = 0;
};

// Concrete attack strategies
class MeleeAttack : public AttackStrategy
{
public:
    void attack() override
    {
        std::cout << "Performs a melee attack!" << std::endl;
    }
};

class RangedAttack : public AttackStrategy
{
public:
    void attack() override
    {
        std::cout << "Shoots a ranged attack!" << std::endl;
    }
};

class MagicAttack : public AttackStrategy
{
public:
    void attack() override
    {
        std::cout << "Casts a magic attack!" << std::endl;
    }
};

// Character class that uses an attack strategy
class Character
{
private:
    AttackStrategy *attackStrategy;

public:
    Character(AttackStrategy *strategy) : attackStrategy(strategy)
    {
    }

    void setAttackStrategy(AttackStrategy *strategy)
    {
        attackStrategy = strategy;
    }

    void performAttack()
    {
        attackStrategy->attack();
    }
};

int main()
{
    // Create different attack strategies
    MeleeAttack melee;
    RangedAttack ranged;
    MagicAttack magic;

    // Create characters with different attack strategies
    Character warrior(&melee);
    Character archer(&ranged);
    Character mage(&magic);

    // Perform attacks
    warrior.performAttack(); // Performs a melee attack
    archer.performAttack();  // Shoots a ranged attack
    mage.performAttack();    // Casts a magic attack

    // Change attack strategy at runtime
    mage.setAttackStrategy(&melee);
    mage.performAttack(); // Now mage performs a melee attack

    return 0;
}
