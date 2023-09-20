#include <iostream>
#include <memory>

// Window Interface
class Window
{
public:
    virtual void renderWindow() = 0;
};

// Concrete Window implementation
class SimpleWindow : public Window
{
public:
    void renderWindow() override
    {
        // Implementation of rendering details
        std::cout << "Rendering a Simple Window\n";
    }
};

// Decorated Window
class DecoratedWindow : public Window
{
public:
    DecoratedWindow(std::shared_ptr<Window> windowReference) : windowReference_(windowReference)
    {
    }

    void renderWindow() override
    {
        if (windowReference_)
        {
            windowReference_->renderWindow();
        }
    }

private:
    std::shared_ptr<Window> windowReference_;
};

// Scrollable Window
class ScrollableWindow : public DecoratedWindow
{
public:
    ScrollableWindow(std::shared_ptr<Window> windowReference) : DecoratedWindow(windowReference)
    {
    }

    void renderWindow() override
    {
        renderScrollBarObject();
        DecoratedWindow::renderWindow();
    }

private:
    void renderScrollBarObject()
    {
        // Prepare and render the scrollbar
        std::cout << "Rendering a Scrollbar\n";
    }
};

int main()
{
    // Create a new window
    std::shared_ptr<Window> window = std::make_shared<SimpleWindow>();
    window->renderWindow();

    // At some point later, add scrolling behavior dynamically
    window = std::make_shared<ScrollableWindow>(window);
    window->renderWindow();

    return 0;
}
