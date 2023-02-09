#include <iostream>
#include <string>
#include <memory>

class Sofa {
public:
    virtual void Show() = 0;
};

class Chair {
public:
    virtual void Show() = 0;
};

class ModernSofa : public Sofa {
 public:
    void Show() { std::cout << "Modern Sofa\n"; }
};

class ModernChair : public Chair {
 public:
    void Show() { std::cout << "Modern Chair\n"; }
};

class VintageSofa : public Sofa {
public:
    void Show() { std::cout << "Vintage Sofa\n"; }
};

class VintageChair : public Chair {
public:
    void Show() { std::cout << "Vintage Chair\n"; }
};

class AbstractFurnitureFactory {
public:
    virtual std::unique_ptr<Sofa> CreateSofa() = 0;
    virtual std::unique_ptr<Chair> CreateChair() = 0;
};

class ModernFurnitureFactory : public AbstractFurnitureFactory {
public:
    std::unique_ptr<Sofa> CreateSofa() {
        return std::make_unique<ModernSofa>();
    }
    std::unique_ptr<Chair> CreateChair() {
        return std::make_unique<ModernChair>();
    }
};

class VintageFurnitureFactory : public AbstractFurnitureFactory {
public:
    std::unique_ptr<Sofa> CreateSofa() {
        return std::make_unique<VintageSofa>();
    }
    std::unique_ptr<Chair> CreateChair() {
        return std::make_unique<VintageChair>();
    }
};

int main() {
    AbstractFurnitureFactory* factory = new VintageFurnitureFactory();
    auto sofa = factory->CreateSofa();
    auto chair = factory->CreateChair();

    sofa->Show();
    chair->Show();

    return 0;
}