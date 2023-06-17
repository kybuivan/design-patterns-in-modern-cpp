#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Component
{
public:
    virtual ~Component() = default;
    virtual void operation() = 0;
    virtual void add(std::shared_ptr<Component> component)
    {
    }
    virtual void remove(std::shared_ptr<Component> component)
    {
    }
    virtual std::shared_ptr<Component> getChild(int index)
    {
        return nullptr;
    }
};

class Leaf : public Component
{
public:
    void operation() override
    {
        std::cout << "Leaf operation" << std::endl;
    }
};

class Composite : public Component
{
public:
    void operation() override
    {
        std::cout << "Composite operation" << std::endl;
        for (const auto &component : components_)
        {
            component->operation();
        }
    }

    void add(std::shared_ptr<Component> component) override
    {
        components_.push_back(component);
    }

    void remove(std::shared_ptr<Component> component) override
    {
        components_.erase(std::remove(components_.begin(), components_.end(), component),
                          components_.end());
    }

    std::shared_ptr<Component> getChild(int index) override
    {
        if (index >= 0 && index < components_.size())
        {
            return components_[index];
        }
        return nullptr;
    }

private:
    std::vector<std::shared_ptr<Component>> components_;
};

int main()
{
    std::shared_ptr<Component> leaf1 = std::make_shared<Leaf>();
    std::shared_ptr<Component> leaf2 = std::make_shared<Leaf>();
    std::shared_ptr<Component> composite = std::make_shared<Composite>();
    composite->add(leaf1);
    composite->add(leaf2);
    composite->operation();

    return 0;
}
