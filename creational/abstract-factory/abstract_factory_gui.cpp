#include <iostream>
#include <memory>

// Abstract Product: Button
class Button
{
public:
    virtual void render() = 0;
};

// Concrete Products: LightButton and DarkButton
class LightButton : public Button
{
public:
    void render() override
    {
        std::cout << "Rendering Light Button" << std::endl;
    }
};

class DarkButton : public Button
{
public:
    void render() override
    {
        std::cout << "Rendering Dark Button" << std::endl;
    }
};

// Abstract Product: Checkbox
class Checkbox
{
public:
    virtual void render() = 0;
};

// Concrete Products: LightCheckbox and DarkCheckbox
class LightCheckbox : public Checkbox
{
public:
    void render() override
    {
        std::cout << "Rendering Light Checkbox" << std::endl;
    }
};

class DarkCheckbox : public Checkbox
{
public:
    void render() override
    {
        std::cout << "Rendering Dark Checkbox" << std::endl;
    }
};

// Abstract Factory
class UIFactory
{
public:
    virtual std::shared_ptr<Button> createButton() = 0;
    virtual std::shared_ptr<Checkbox> createCheckbox() = 0;
};

// Concrete Factories: LightThemeFactory and DarkThemeFactory
class LightThemeFactory : public UIFactory
{
public:
    std::shared_ptr<Button> createButton() override
    {
        return std::make_shared<LightButton>();
    }
    std::shared_ptr<Checkbox> createCheckbox() override
    {
        return std::make_shared<LightCheckbox>();
    }
};

class DarkThemeFactory : public UIFactory
{
public:
    std::shared_ptr<Button> createButton() override
    {
        return std::make_shared<DarkButton>();
    }
    std::shared_ptr<Checkbox> createCheckbox() override
    {
        return std::make_shared<DarkCheckbox>();
    }
};

// Client
class Application
{
public:
    Application(std::shared_ptr<UIFactory> factory) : factory(factory)
    {
    }

    void createUI()
    {
        std::shared_ptr<Button> button = factory->createButton();
        std::shared_ptr<Checkbox> checkbox = factory->createCheckbox();

        button->render();
        checkbox->render();
    }

private:
    std::shared_ptr<UIFactory> factory;
};

int main()
{
    std::shared_ptr<UIFactory> lightFactory = std::make_shared<LightThemeFactory>();
    std::shared_ptr<UIFactory> darkFactory = std::make_shared<DarkThemeFactory>();

    Application lightApp(lightFactory);
    Application darkApp(darkFactory);

    std::cout << "Light Theme:" << std::endl;
    lightApp.createUI();

    std::cout << "\nDark Theme:" << std::endl;
    darkApp.createUI();

    return 0;
}
