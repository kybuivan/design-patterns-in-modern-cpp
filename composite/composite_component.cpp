#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Component
{
public:
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
        components_.erase(
            std::remove_if(components_.begin(),
                           components_.end(),
                           [component](const auto &c) { return c.get() == component.get(); }),
            components_.end());
    }

    std::shared_ptr<Component> getChild(int index) override
    {
        return components_[index];
    }

private:
    std::vector<std::shared_ptr<Component>> components_;
};

int main()
{
    std::shared_ptr<Leaf> leaf1 = std::make_shared<Leaf>();
    std::shared_ptr<Leaf> leaf2 = std::make_shared<Leaf>();
    std::shared_ptr<Composite> composite = std::make_shared<Composite>();
    composite->add(leaf1);
    composite->add(leaf2);
    composite->operation();
    return 0;
}
