#include <iostream>
#include <memory>
#include <string>

class Sofa
{
public:
    virtual ~Sofa() = default;
    virtual void Show() = 0;
};

class Chair
{
public:
    virtual ~Chair() = default;
    virtual void Show() = 0;
};

class ModernSofa : public Sofa
{
public:
    void Show() override
    {
        std::cout << "Modern Sofa\n";
    }
};

class ModernChair : public Chair
{
public:
    void Show() override
    {
        std::cout << "Modern Chair\n";
    }
};

class VintageSofa : public Sofa
{
public:
    void Show() override
    {
        std::cout << "Vintage Sofa\n";
    }
};

class VintageChair : public Chair
{
public:
    void Show() override
    {
        std::cout << "Vintage Chair\n";
    }
};

class AbstractFurnitureFactory
{
public:
    virtual ~AbstractFurnitureFactory() = default;
    virtual std::unique_ptr<Sofa> CreateSofa() = 0;
    virtual std::unique_ptr<Chair> CreateChair() = 0;
};

class ModernFurnitureFactory : public AbstractFurnitureFactory
{
public:
    std::unique_ptr<Sofa> CreateSofa() override
    {
        return std::make_unique<ModernSofa>();
    }
    std::unique_ptr<Chair> CreateChair() override
    {
        return std::make_unique<ModernChair>();
    }
};

class VintageFurnitureFactory : public AbstractFurnitureFactory
{
public:
    std::unique_ptr<Sofa> CreateSofa() override
    {
        return std::make_unique<VintageSofa>();
    }
    std::unique_ptr<Chair> CreateChair() override
    {
        return std::make_unique<VintageChair>();
    }
};

int main()
{
    std::unique_ptr<AbstractFurnitureFactory> factory = std::make_unique<VintageFurnitureFactory>();
    std::unique_ptr<Sofa> sofa = factory->CreateSofa();
    std::unique_ptr<Chair> chair = factory->CreateChair();

    sofa->Show();
    chair->Show();

    return 0;
}
