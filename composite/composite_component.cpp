#include <iostream>
#include <vector>

class Component
{
public:
    virtual void operation() = 0;
    virtual void add(Component *component)
    {
    }
    virtual void remove(Component *component)
    {
    }
    virtual Component *getChild(int index)
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
        for (auto &component : components_)
        {
            component->operation();
        }
    }

    void add(Component *component) override
    {
        components_.push_back(component);
    }

    void remove(Component *component) override
    {
        components_.erase(std::remove(components_.begin(), components_.end(), component),
                          components_.end());
    }

    Component *getChild(int index) override
    {
        return components_[index];
    }

private:
    std::vector<Component *> components_;
};

int main()
{
    Leaf leaf1;
    Leaf leaf2;
    Composite composite;
    composite.add(&leaf1);
    composite.add(&leaf2);
    composite.operation();
    return 0;
}
