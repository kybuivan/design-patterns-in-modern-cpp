#include <iostream>
#include <memory>
#include <vector>

// Component interface representing a game character
class Player
{
public:
    virtual void display() = 0;
    virtual ~Player() = default;
};

// Concrete implementation of Player
class BasePlayer : public Player
{
public:
    void display() override
    {
        std::cout << "Player" << std::endl;
    }
};

// Decorator interface
class PlayerDecorator : public Player
{
protected:
    std::shared_ptr<Player> player;

public:
    PlayerDecorator(std::shared_ptr<Player> player) : player(player)
    {
    }

    void display() override
    {
        player->display();
    }
};

// Concrete decorator representing the ability to fly
class FlyDecorator : public PlayerDecorator
{
public:
    FlyDecorator(std::shared_ptr<Player> player) : PlayerDecorator(player)
    {
    }

    void display() override
    {
        PlayerDecorator::display();
        std::cout << "Ability: Flying" << std::endl;
    }
};

// Concrete decorator representing the ability to become invisible
class InvisibilityDecorator : public PlayerDecorator
{
public:
    InvisibilityDecorator(std::shared_ptr<Player> player) : PlayerDecorator(player)
    {
    }

    void display() override
    {
        PlayerDecorator::display();
        std::cout << "Ability: Invisibility" << std::endl;
    }
};

// Concrete decorator representing increased speed
class SpeedDecorator : public PlayerDecorator
{
public:
    SpeedDecorator(std::shared_ptr<Player> player) : PlayerDecorator(player)
    {
    }

    void display() override
    {
        PlayerDecorator::display();
        std::cout << "Ability: Increased Speed" << std::endl;
    }
};

int main()
{
    // Create a base player character
    std::shared_ptr<Player> player = std::make_shared<BasePlayer>();

    // Decorate the player character with abilities
    std::shared_ptr<Player> flyingPlayer = std::make_shared<FlyDecorator>(player);
    std::shared_ptr<Player> invisibleFlyingPlayer = std::make_shared<InvisibilityDecorator>(flyingPlayer);
    std::shared_ptr<Player> superPlayer = std::make_shared<SpeedDecorator>(invisibleFlyingPlayer);

    // Display the player character with abilities
    std::vector<std::shared_ptr<Player>> players = {player, flyingPlayer, invisibleFlyingPlayer, superPlayer};
    for (const auto &p : players)
    {
        p->display();
        std::cout << "-----------------------" << std::endl;
    }

    return 0;
}
