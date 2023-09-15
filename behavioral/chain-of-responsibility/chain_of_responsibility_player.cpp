#include <iostream>
#include <memory>
#include <string>

class Enemy
{
public:
    Enemy(const std::string &name, int resistance) : name_(name), resistance_(resistance)
    {
    }

    const std::string &getName() const
    {
        return name_;
    }

    int getResistance() const
    {
        return resistance_;
    }

private:
    std::string name_;
    int resistance_;
};

class Player
{
public:
    Player(const std::string &name, int attackPower, int xpRequiredToLevelUp)
        : name_(name), attackPower_(attackPower), xp_(0), xpRequiredToLevelUp_(xpRequiredToLevelUp),
          nextPlayer_(nullptr)
    {
    }

    void setNextPlayer(std::shared_ptr<Player> nextPlayer)
    {
        nextPlayer_ = nextPlayer;
    }

    void attack(std::shared_ptr<Enemy> enemy)
    {
        if (canDefeat(enemy))
        {
            std::cout << name_ << " defeats " << enemy->getName() << " with " << attackPower_ << " attack power."
                      << std::endl;
            gainXP(10); // Gain XP when defeating an enemy
        }
        else if (nextPlayer_)
        {
            nextPlayer_->attack(enemy);
        }
        else
        {
            std::cout << name_ << " cannot defeat " << enemy->getName() << "." << std::endl;
        }
    }

    void gainXP(int xp)
    {
        xp_ += xp;
        if (xp_ >= xpRequiredToLevelUp_)
        {
            levelUp();
        }
    }

    void levelUp()
    {
        attackPower_ += 20; // Increase attack power on leveling up
        xp_ -= xpRequiredToLevelUp_;
        xpRequiredToLevelUp_ += 50; // Increase XP required for the next level
        std::cout << name_ << " leveled up! New attack power: " << attackPower_ << std::endl;
    }

protected:
    bool canDefeat(std::shared_ptr<Enemy> enemy)
    {
        return attackPower_ >= enemy->getResistance();
    }

private:
    std::string name_;
    int attackPower_;
    int xp_;
    int xpRequiredToLevelUp_;
    std::shared_ptr<Player> nextPlayer_;
};

int main()
{
    // Create players with different attack powers and XP requirements
    std::shared_ptr<Player> player1 = std::make_shared<Player>("Warrior", 100, 20);
    std::shared_ptr<Player> player2 = std::make_shared<Player>("Mage", 80, 40);
    std::shared_ptr<Player> player3 = std::make_shared<Player>("Archer", 60, 60);

    // Set up the Chain of Responsibility
    player1->setNextPlayer(player2);
    player2->setNextPlayer(player3);

    // Create enemies with different resistances
    std::shared_ptr<Enemy> enemy1 = std::make_shared<Enemy>("Dragon", 120);
    std::shared_ptr<Enemy> enemy2 = std::make_shared<Enemy>("Orc", 90);
    std::shared_ptr<Enemy> enemy3 = std::make_shared<Enemy>("Goblin", 50);

    // Players attack enemies
    player1->attack(enemy1);
    player1->attack(enemy2);
    player1->attack(enemy3);
    player1->attack(enemy3);
    player1->attack(enemy3);
    player1->attack(enemy3);

    return 0;
}
