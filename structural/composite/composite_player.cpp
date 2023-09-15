#include <iostream>
#include <vector>

// Abstract base class for game components
class Component
{
public:
    virtual ~Component() = default;
    virtual void update() = 0;
};

// Concrete component for input handling
class InputComponent : public Component
{
public:
    void update() override
    {
        std::cout << "Input component updated." << std::endl;
    }
};

// Concrete component for graphics rendering
class GraphicsComponent : public Component
{
public:
    void update() override
    {
        std::cout << "Graphics component updated." << std::endl;
    }
};

// Concrete component for sound
class SoundComponent : public Component
{
public:
    void update() override
    {
        std::cout << "Sound component updated." << std::endl;
    }
};

// Concrete component for physics simulation
class PhysicsComponent : public Component
{
public:
    void update() override
    {
        std::cout << "Physics component updated." << std::endl;
    }
};

// Composite class representing a game entity
class Entity
{
private:
    std::vector<Component *> components;

public:
    void addComponent(Component *component)
    {
        components.push_back(component);
    }

    void update()
    {
        for (Component *component : components)
        {
            component->update();
        }
    }
};

int main()
{
    // Create components
    InputComponent input;
    GraphicsComponent graphics;
    SoundComponent sound;
    PhysicsComponent physics;

    // Create a game entity and add components
    Entity player;
    player.addComponent(&input);
    player.addComponent(&graphics);
    player.addComponent(&sound);
    player.addComponent(&physics);

    // Update the game entity, which will update all its components
    player.update();

    return 0;
}
