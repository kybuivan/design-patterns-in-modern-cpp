#include <iostream>
#include <string>
#include <vector>

// Observer abstract base class
class Observer
{
public:
    virtual void update(const std::string &message) = 0;
};

// Concrete Observer representing game objects
class GameObject : public Observer
{
private:
    std::string name;

public:
    GameObject(const std::string &name) : name(name)
    {
    }

    void update(const std::string &message) override
    {
        std::cout << "Object " << name << " received message: " << message << std::endl;
    }
};

// Subject abstract base class
class Subject
{
private:
    std::vector<Observer *> observers;

public:
    void addObserver(Observer *observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(Observer *observer)
    {
        // Remove the observer (not implemented here)
    }

    void notifyObservers(const std::string &message)
    {
        for (Observer *observer : observers)
        {
            observer->update(message);
        }
    }
};

// Concrete Subject representing the game state
class GameState : public Subject
{
private:
    std::string state;

public:
    void setState(const std::string &newState)
    {
        state = newState;
        notifyObservers(newState);
    }
};

int main()
{
    // Create game objects
    GameObject player("Player");
    GameObject enemy("Enemy");
    GameObject treasure("Treasure");

    // Create the game state
    GameState gameState;

    // Register game objects as observers
    gameState.addObserver(&player);
    gameState.addObserver(&enemy);
    gameState.addObserver(&treasure);

    // Simulate game state changes
    gameState.setState("Player collected a treasure");
    gameState.setState("Player defeated an enemy");

    return 0;
}
