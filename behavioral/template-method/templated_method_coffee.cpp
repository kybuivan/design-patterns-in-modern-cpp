#include <iostream>
#include <string>

// Abstract base class defining the template method
class BeverageTemplate
{
public:
    // The template method for preparing the beverage
    void prepareBeverage()
    {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

protected:
    // Abstract methods to be implemented by subclasses
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    // Common methods shared among subclasses
    void boilWater()
    {
        std::cout << "Boiling water..." << std::endl;
    }

    void pourInCup()
    {
        std::cout << "Pouring into cup..." << std::endl;
    }
};

// Concrete subclass for preparing coffee
class Coffee : public BeverageTemplate
{
protected:
    void brew() override
    {
        std::cout << "Dripping coffee through filter..." << std::endl;
    }

    void addCondiments() override
    {
        std::cout << "Adding sugar and milk..." << std::endl;
    }
};

// Concrete subclass for preparing tea
class Tea : public BeverageTemplate
{
protected:
    void brew() override
    {
        std::cout << "Steeping the tea..." << std::endl;
    }

    void addCondiments() override
    {
        std::cout << "Adding lemon..." << std::endl;
    }
};

int main()
{
    // Prepare and serve coffee
    Coffee coffee;
    std::cout << "Making Coffee:" << std::endl;
    coffee.prepareBeverage();

    std::cout << std::endl;

    // Prepare and serve tea
    Tea tea;
    std::cout << "Making Tea:" << std::endl;
    tea.prepareBeverage();

    return 0;
}
