#include <iostream>
#include <memory>
#include <string>

// Abstract base class for handling GUI events
class EventHandler
{
public:
    virtual ~EventHandler() = default;
    virtual void handleEvent(const std::string &event) = 0;
    void setNextHandler(std::shared_ptr<EventHandler> next)
    {
        nextHandler_ = next;
    }
    void passEvent(const std::string &event)
    {
        if (nextHandler_)
        {
            nextHandler_->handleEvent(event);
        }
        else
        {
            std::cout << "Event unhandled: " << event << std::endl;
        }
    }

private:
    std::shared_ptr<EventHandler> nextHandler_;
};

// Concrete handler for buttons
class ButtonHandler : public EventHandler
{
public:
    void handleEvent(const std::string &event) override
    {
        if (event == "Click")
        {
            std::cout << "Button clicked, performing action." << std::endl;
        }
        else
        {
            passEvent(event);
        }
    }
};

// Concrete handler for forms
class FormHandler : public EventHandler
{
public:
    void handleEvent(const std::string &event) override
    {
        if (event == "Submit")
        {
            std::cout << "Form submitted, processing data." << std::endl;
        }
        else
        {
            passEvent(event);
        }
    }
};

// Concrete handler for the main application window
class MainWindowHandler : public EventHandler
{
public:
    void handleEvent(const std::string &event) override
    {
        if (event == "Close")
        {
            std::cout << "Main window closed." << std::endl;
        }
        else
        {
            passEvent(event);
        }
    }
};

// Concrete handler for panels
class PanelHandler : public EventHandler
{
public:
    void handleEvent(const std::string &event) override
    {
        if (event == "PanelEvent")
        {
            std::cout << "Panel received an event." << std::endl;
        }
        else
        {
            passEvent(event);
        }
    }
};

// Concrete handler for toolbars
class ToolbarHandler : public EventHandler
{
public:
    void handleEvent(const std::string &event) override
    {
        if (event == "ToolbarEvent")
        {
            std::cout << "Toolbar received an event." << std::endl;
        }
        else
        {
            passEvent(event);
        }
    }
};

// Concrete handler for subpanels
class SubPanelHandler : public EventHandler
{
public:
    void handleEvent(const std::string &event) override
    {
        if (event == "SubPanelEvent")
        {
            std::cout << "SubPanel received an event." << std::endl;
        }
        else
        {
            passEvent(event);
        }
    }
};

// Concrete handler for inputs
class InputHandler : public EventHandler
{
public:
    void handleEvent(const std::string &event) override
    {
        if (event == "InputEvent")
        {
            std::cout << "Input received an event." << std::endl;
        }
        else
        {
            passEvent(event);
        }
    }
};

// Concrete handler for text elements
class TextHandler : public EventHandler
{
public:
    void handleEvent(const std::string &event) override
    {
        if (event == "TextEvent")
        {
            std::cout << "Text element received an event." << std::endl;
        }
        else
        {
            passEvent(event);
        }
    }
};

// Concrete handler for images
class ImageHandler : public EventHandler
{
public:
    void handleEvent(const std::string &event) override
    {
        if (event == "ImageEvent")
        {
            std::cout << "Image received an event." << std::endl;
        }
        else
        {
            passEvent(event);
        }
    }
};

int main()
{
    // Create event handlers using shared_ptr
    auto buttonHandler = std::make_shared<ButtonHandler>();
    auto formHandler = std::make_shared<FormHandler>();
    auto mainWindowHandler = std::make_shared<MainWindowHandler>();
    auto panelHandler = std::make_shared<PanelHandler>();
    auto toolbarHandler = std::make_shared<ToolbarHandler>();
    auto subPanelHandler = std::make_shared<SubPanelHandler>();
    auto inputHandler = std::make_shared<InputHandler>();
    auto textHandler = std::make_shared<TextHandler>();
    auto imageHandler = std::make_shared<ImageHandler>();

    // Set up the chain of responsibility
    buttonHandler->setNextHandler(formHandler);
    formHandler->setNextHandler(mainWindowHandler);
    mainWindowHandler->setNextHandler(panelHandler);
    panelHandler->setNextHandler(toolbarHandler);
    toolbarHandler->setNextHandler(subPanelHandler);
    subPanelHandler->setNextHandler(inputHandler);
    inputHandler->setNextHandler(textHandler);
    textHandler->setNextHandler(imageHandler);

    // Simulate GUI events
    buttonHandler->handleEvent("Click");
    toolbarHandler->handleEvent("ToolbarEvent");
    imageHandler->handleEvent("ImageEvent");
    subPanelHandler->handleEvent("SubPanelEvent");
    textHandler->handleEvent("TextEvent");
    panelHandler->handleEvent("PanelEvent");
    formHandler->handleEvent("Submit");
    mainWindowHandler->handleEvent("Close");
    buttonHandler->handleEvent("KeyPress"); // Unhandled event

    return 0;
}
