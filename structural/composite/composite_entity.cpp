#include <iostream>
#include <memory>
#include <vector>

class Component
{
public:
    virtual ~Component() = default;
    virtual void update() = 0;
};

class RenderComponent : public Component
{
public:
    void update() override
    {
        std::cout << "Rendering component updated." << std::endl;
    }
};

class PhysicsComponent : public Component
{
public:
    void update() override
    {
        std::cout << "Physics component updated." << std::endl;
    }
};

class AIComponent : public Component
{
public:
    void update() override
    {
        std::cout << "AI component updated." << std::endl;
    }
};

class Entity
{
private:
    std::vector<std::shared_ptr<Component>> components;
    std::vector<std::shared_ptr<Entity>> children;

public:
    void addComponent(std::shared_ptr<Component> component)
    {
        components.push_back(component);
    }

    void addChild(std::shared_ptr<Entity> entity)
    {
        children.push_back(entity);
    }

    void update()
    {
        for (const auto &component : components)
        {
            component->update();
        }

        for (const auto &entity : children)
        {
            entity->update();
        }
    }
};

int main()
{
    auto renderer = std::make_shared<RenderComponent>();
    auto physicsSimulator = std::make_shared<PhysicsComponent>();
    auto aiController = std::make_shared<AIComponent>();

    auto player = std::make_shared<Entity>();
    player->addComponent(renderer);
    player->addComponent(physicsSimulator);

    auto enemy = std::make_shared<Entity>();
    enemy->addComponent(renderer);
    enemy->addComponent(physicsSimulator);
    enemy->addComponent(aiController);

    auto gameWorld = std::make_shared<Entity>();
    gameWorld->addChild(player);
    gameWorld->addChild(enemy);

    gameWorld->update();

    return 0;
}
