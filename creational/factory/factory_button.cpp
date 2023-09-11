#include <iostream>
#include <memory>
#include <string>

class Button
{
public:
    virtual ~Button() = default;
    virtual void paint() = 0;
};

class MacOSButton : public Button
{
public:
    void paint() override
    {
        std::cout << "Rendering a MacOS button\n";
    }
};

class WindowsButton : public Button
{
public:
    void paint() override
    {
        std::cout << "Rendering a Windows button\n";
    }
};

class Dialog
{
public:
    virtual ~Dialog() = default;
    virtual std::unique_ptr<Button> createButton() = 0;
    void render()
    {
        std::unique_ptr<Button> button = createButton();
        button->paint();
    }
};

class MacOSDialog : public Dialog
{
public:
    std::unique_ptr<Button> createButton() override
    {
        return std::make_unique<MacOSButton>();
    }
};

class WindowsDialog : public Dialog
{
public:
    std::unique_ptr<Button> createButton() override
    {
        return std::make_unique<WindowsButton>();
    }
};

class GUIFactory
{
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Dialog> createDialog() = 0;
};

class MacOSFactory : public GUIFactory
{
public:
    std::unique_ptr<Dialog> createDialog() override
    {
        return std::make_unique<MacOSDialog>();
    }
};

class WindowsFactory : public GUIFactory
{
public:
    std::unique_ptr<Dialog> createDialog() override
    {
        return std::make_unique<WindowsDialog>();
    }
};

int main()
{
    std::unique_ptr<GUIFactory> factory = std::make_unique<MacOSFactory>();
    std::unique_ptr<Dialog> dialog = factory->createDialog();
    dialog->render();

    return 0;
}
