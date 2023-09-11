#include <iostream>
#include <map>
#include <memory>
#include <string>

class Window
{
public:
    virtual ~Window() = default;
    virtual std::unique_ptr<Window> clone() = 0;
    virtual void display() = 0;
};

class ApplicationWindow : public Window
{
public:
    ApplicationWindow()
    {
        std::cout << "ApplicationWindow created." << std::endl;
    }
    std::unique_ptr<Window> clone() override
    {
        return std::make_unique<ApplicationWindow>(*this);
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
    std::unique_ptr<Window> clone() override
    {
        return std::make_unique<DialogWindow>(*this);
    }
    void display() override
    {
        std::cout << "Displaying DialogWindow." << std::endl;
    }
};

class WindowRegistry
{
private:
    std::map<std::string, std::unique_ptr<Window>> windows;

public:
    void register_window(const std::string &key, std::unique_ptr<Window> window)
    {
        windows[key] = std::move(window);
    }

    std::unique_ptr<Window> get_window(const std::string &key)
    {
        return windows[key]->clone();
    }
};

int main()
{
    WindowRegistry registry;
    registry.register_window("application", std::make_unique<ApplicationWindow>());
    registry.register_window("dialog", std::make_unique<DialogWindow>());

    std::unique_ptr<Window> window1 = registry.get_window("application");
    window1->display();

    std::unique_ptr<Window> window2 = registry.get_window("dialog");
    window2->display();

    return 0;
}
