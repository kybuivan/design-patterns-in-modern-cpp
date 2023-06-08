#include <iostream>
#include <string>

class Button
{
public:
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
    virtual Button *createButton() = 0;
    void render()
    {
        Button *button = createButton();
        button->paint();
    }
};

class MacOSDialog : public Dialog
{
public:
    Button *createButton() override
    {
        return new MacOSButton;
    }
};

class WindowsDialog : public Dialog
{
public:
    Button *createButton() override
    {
        return new WindowsButton;
    }
};

class GUIFactory
{
public:
    virtual Dialog *createDialog() = 0;
};

class MacOSFactory : public GUIFactory
{
public:
    Dialog *createDialog() override
    {
        return new MacOSDialog;
    }
};

class WindowsFactory : public GUIFactory
{
public:
    Dialog *createDialog() override
    {
        return new WindowsDialog;
    }
};

int main()
{
    GUIFactory *factory = new MacOSFactory;
    Dialog *dialog = factory->createDialog();
    dialog->render();
    delete dialog;
    delete factory;
    return 0;
}
