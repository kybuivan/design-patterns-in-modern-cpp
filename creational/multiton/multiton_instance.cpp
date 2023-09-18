#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// Abstract base class for game objects
class GameObject
{
public:
    virtual void render() = 0;
};

// Concrete game object types
class Player : public GameObject
{
public:
    void render() override
    {
        std::cout << "Rendering Player" << std::endl;
    }
};

class Enemy : public GameObject
{
public:
    void render() override
    {
        std::cout << "Rendering Enemy" << std::endl;
    }
};

class Projectile : public GameObject
{
public:
    void render() override
    {
        std::cout << "Rendering Projectile" << std::endl;
    }
};

class Multiton
{
private:
    static std::unordered_map<std::string, std::shared_ptr<GameObject>> instances;

public:
    static std::shared_ptr<GameObject> getInstance(const std::string &key)
    {
        if (instances.find(key) == instances.end())
        {
            // Create a new instance based on the key
            if (key == "Player")
            {
                instances[key] = std::make_shared<Player>();
            }
            else if (key == "Enemy")
            {
                instances[key] = std::make_shared<Enemy>();
            }
            else if (key == "Projectile")
            {
                instances[key] = std::make_shared<Projectile>();
            }
        }
        return instances[key];
    }
};

std::unordered_map<std::string, std::shared_ptr<GameObject>> Multiton::instances;

int main()
{
    // Get or create game object instances by keys
    std::shared_ptr<GameObject> player = Multiton::getInstance("Player");
    std::shared_ptr<GameObject> enemy = Multiton::getInstance("Enemy");
    std::shared_ptr<GameObject> projectile = Multiton::getInstance("Projectile");

    // Use the game objects
    player->render();
    enemy->render();
    projectile->render();

    return 0;
}
