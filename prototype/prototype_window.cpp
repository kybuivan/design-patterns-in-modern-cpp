#include <iostream>
#include <map>
#include <string>

class Window
{
public:
    virtual Window *clone() = 0;
    virtual void display() = 0;
};

class ApplicationWindow : public Window
{
public:
    ApplicationWindow()
    {
        std::cout << "ApplicationWindow created." << std::endl;
    }
    Window *clone() override
    {
        return new ApplicationWindow();
    }
    void display() override
    {
        std::cout << "Displaying ApplicationWindow." << std::endl;
    }
};

class DialogWindow : public Window
{
public:
    DialogWindow()
    {
        std::cout << "DialogWindow created." << std::endl;
    }
    Window *clone() override
    {
        return new DialogWindow();
    }
    void display() override
    {
        std::cout << "Displaying DialogWindow." << std::endl;
    }
};

class WindowRegistry
{
private:
    std::map<std::string, Window *> windows;

public:
    void register_window(const std::string &key, Window *window)
    {
        windows[key] = window;
    }

    Window *get_window(const std::string &key)
    {
        return windows[key]->clone();
    }
};

int main()
{
    WindowRegistry registry;
    registry.register_window("application", new ApplicationWindow());
    registry.register_window("dialog", new DialogWindow());

    Window *window1 = registry.get_window("application");
    window1->display();

    Window *window2 = registry.get_window("dialog");
    window2->display();

    return 0;
}
