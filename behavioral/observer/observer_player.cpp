#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Observer
{
public:
    virtual void update(const std::string &message) = 0;
};

class Player : public Observer
{
private:
    std::string name;

public:
    Player(const std::string &name) : name(name)
    {
    }

    void update(const std::string &message) override
    {
        std::cout << "Player " << name << " earned achievement: " << message << std::endl;
    }
};

class Subject
{
private:
    std::vector<std::shared_ptr<Observer>> observers;

public:
    void addObserver(const std::shared_ptr<Observer> &observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(const std::shared_ptr<Observer> &observer)
    {
        // Remove the observer (not implemented here)
    }

    void notifyObservers(const std::string &message)
    {
        for (const auto &observer : observers)
        {
            observer->update(message);
        }
    }
};

class AchievementSystem : public Subject
{
public:
    void unlockAchievement(const std::string &achievementName)
    {
        std::cout << "Achievement unlocked: " << achievementName << std::endl;
        notifyObservers(achievementName);
    }
};

int main()
{
    // Create players as shared_ptr instances
    auto player1 = std::make_shared<Player>("Player 1");
    auto player2 = std::make_shared<Player>("Player 2");

    // Create the achievement system
    AchievementSystem achievementSystem;

    // Register players as observers of the achievement system
    achievementSystem.addObserver(player1);
    achievementSystem.addObserver(player2);

    // Simulate players earning achievements
    achievementSystem.unlockAchievement("First Blood");
    achievementSystem.unlockAchievement("Treasure Hunter");
    achievementSystem.unlockAchievement("Master Explorer");

    return 0;
}
