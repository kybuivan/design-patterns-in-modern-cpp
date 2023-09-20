#include <iostream>
#include <memory>

// Abstract Handler: EventHandler
class EventHandler
{
public:
    virtual void HandleEvent(const std::string &event) = 0;
    virtual void SetNextHandler(std::shared_ptr<EventHandler> handler) = 0;
};

// Concrete Handler: MouseClickHandler
class MouseClickHandler : public EventHandler
{
public:
    void HandleEvent(const std::string &event) override
    {
        if (event == "MouseClick")
        {
            std::cout << "MouseClickHandler handled the event." << std::endl;
        }
        else if (nextHandler != nullptr)
        {
            nextHandler->HandleEvent(event);
        }
        else
        {
            std::cout << "No handler can handle the event." << std::endl;
        }
    }

    void SetNextHandler(std::shared_ptr<EventHandler> handler) override
    {
        nextHandler = handler;
    }

private:
    std::shared_ptr<EventHandler> nextHandler;
};

// Concrete Handler: KeyPressHandler
class KeyPressHandler : public EventHandler
{
public:
    void HandleEvent(const std::string &event) override
    {
        if (event == "KeyPress_Enter")
        {
            std::cout << "KeyPressHandler (Enter) handled the event." << std::endl;
        }
        else if (event == "KeyPress_Delete")
        {
            std::cout << "KeyPressHandler (Delete) handled the event." << std::endl;
        }
        else if (nextHandler != nullptr)
        {
            nextHandler->HandleEvent(event);
        }
        else
        {
            std::cout << "No handler can handle the event." << std::endl;
        }
    }

    void SetNextHandler(std::shared_ptr<EventHandler> handler) override
    {
        nextHandler = handler;
    }

private:
    std::shared_ptr<EventHandler> nextHandler;
};

int main()
{
    // Create a chain of event handlers
    std::shared_ptr<EventHandler> mouseClickHandler = std::make_shared<MouseClickHandler>();
    std::shared_ptr<EventHandler> keyPressHandler = std::make_shared<KeyPressHandler>();

    // Set up the chain
    mouseClickHandler->SetNextHandler(keyPressHandler);

    // Simulate GUI events
    mouseClickHandler->HandleEvent("MouseClick");
    mouseClickHandler->HandleEvent("KeyPress_Enter");
    mouseClickHandler->HandleEvent("KeyPress_Delete");
    mouseClickHandler->HandleEvent("UnknownEvent");

    return 0;
}
