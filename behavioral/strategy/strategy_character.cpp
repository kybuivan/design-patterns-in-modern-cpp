#include <iostream>
#include <memory>

// Abstract base class for movement strategies
class MovementStrategy
{
public:
    virtual void move() = 0;
};

// Concrete movement strategies
class WalkStrategy : public MovementStrategy
{
public:
    void move() override
    {
        std::cout << "Character is walking." << std::endl;
    }
};

class RunStrategy : public MovementStrategy
{
public:
    void move() override
    {
        std::cout << "Character is running." << std::endl;
    }
};

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

// Character class that uses movement and attack strategies
class Character
{
private:
    std::shared_ptr<MovementStrategy> movementStrategy;
    std::shared_ptr<AttackStrategy> attackStrategy;

public:
    Character(std::shared_ptr<MovementStrategy> moveStrat, std::shared_ptr<AttackStrategy> attackStrat)
        : movementStrategy(moveStrat), attackStrategy(attackStrat)
    {
    }

    void setMovementStrategy(std::shared_ptr<MovementStrategy> moveStrat)
    {
        movementStrategy = moveStrat;
    }

    void setAttackStrategy(std::shared_ptr<AttackStrategy> attackStrat)
    {
        attackStrategy = attackStrat;
    }

    void performMove()
    {
        movementStrategy->move();
    }

    void performAttack()
    {
        attackStrategy->attack();
    }
};

int main()
{
    // Create different movement and attack strategies
    auto walk = std::make_shared<WalkStrategy>();
    auto run = std::make_shared<RunStrategy>();
    auto meleeAttack = std::make_shared<MeleeAttack>();
    auto rangedAttack = std::make_shared<RangedAttack>();

    // Create characters with different strategies
    Character warrior(walk, meleeAttack);
    Character archer(run, rangedAttack);

    // Perform actions
    warrior.performMove();   // Character is walking.
    warrior.performAttack(); // Performs a melee attack!

    archer.performMove();   // Character is running.
    archer.performAttack(); // Shoots a ranged attack.

    // Change strategies at runtime
    warrior.setMovementStrategy(run);
    warrior.setAttackStrategy(rangedAttack);

    warrior.performMove();   // Character is running.
    warrior.performAttack(); // Shoots a ranged attack.

    return 0;
}
