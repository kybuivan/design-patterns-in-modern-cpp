#include <iostream>
#include <memory>
#include <string>

// Abstract Product: Button
class Button
{
public:
    virtual void Render() = 0;
};

// Concrete Product: WindowsButton
class WindowsButton : public Button
{
public:
    void Render() override
    {
        std::cout << "Rendering a Windows-style button." << std::endl;
    }
};

// Concrete Product: MotifButton
class MotifButton : public Button
{
public:
    void Render() override
    {
        std::cout << "Rendering a Motif-style button." << std::endl;
    }
};

// Abstract Product: EditBox
class EditBox
{
public:
    virtual void Render() = 0;
};

// Concrete Product: WindowsEditBox
class WindowsEditBox : public EditBox
{
public:
    void Render() override
    {
        std::cout << "Rendering a Windows-style edit box." << std::endl;
    }
};

// Concrete Product: MotifEditBox
class MotifEditBox : public EditBox
{
public:
    void Render() override
    {
        std::cout << "Rendering a Motif-style edit box." << std::endl;
    }
};

// Abstract Factory: LookAndFeel
class LookAndFeel
{
public:
    virtual std::shared_ptr<Button> CreateButton() = 0;
    virtual std::shared_ptr<EditBox> CreateEditBox() = 0;
};

// Concrete Factory: WindowsLookAndFeel
class WindowsLookAndFeel : public LookAndFeel
{
public:
    std::shared_ptr<Button> CreateButton() override
    {
        return std::make_shared<WindowsButton>();
    }

    std::shared_ptr<EditBox> CreateEditBox() override
    {
        return std::make_shared<WindowsEditBox>();
    }
};

// Concrete Factory: MotifLookAndFeel
class MotifLookAndFeel : public LookAndFeel
{
public:
    std::shared_ptr<Button> CreateButton() override
    {
        return std::make_shared<MotifButton>();
    }

    std::shared_ptr<EditBox> CreateEditBox() override
    {
        return std::make_shared<MotifEditBox>();
    }
};

int main()
{
    // Choose the look and feel theme based on a configuration parameter
    std::shared_ptr<LookAndFeel> lookAndFeel;
    std::string theme = "Motif"; // Change this to "Windows" to switch themes

    if (theme == "Windows")
    {
        lookAndFeel = std::make_shared<WindowsLookAndFeel>();
    }
    else if (theme == "Motif")
    {
        lookAndFeel = std::make_shared<MotifLookAndFeel>();
    }
    else
    {
        std::cout << "Invalid theme." << std::endl;
        return 1;
    }

    // Create GUI elements using the selected look and feel
    std::shared_ptr<Button> button = lookAndFeel->CreateButton();
    std::shared_ptr<EditBox> editBox = lookAndFeel->CreateEditBox();

    // Render the GUI elements
    button->Render();
    editBox->Render();

    return 0;
}
