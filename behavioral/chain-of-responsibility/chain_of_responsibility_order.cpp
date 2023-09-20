#include <iostream>
#include <memory>
#include <string>

// Abstract Handler: OrderHandler
class OrderHandler
{
public:
    virtual void HandleOrder(const std::string &orderDetails) = 0;
    virtual void SetNextHandler(std::shared_ptr<OrderHandler> handler) = 0;
};

// Concrete Handler: SmallOrderHandler
class SmallOrderHandler : public OrderHandler
{
public:
    void HandleOrder(const std::string &orderDetails) override
    {
        if (orderDetails.find("small") != std::string::npos)
        {
            std::cout << "SmallOrderHandler is handling the order: " << orderDetails << std::endl;
        }
        else if (nextHandler != nullptr)
        {
            nextHandler->HandleOrder(orderDetails);
        }
        else
        {
            std::cout << "No handler can handle the order: " << orderDetails << std::endl;
        }
    }

    void SetNextHandler(std::shared_ptr<OrderHandler> handler) override
    {
        nextHandler = handler;
    }

private:
    std::shared_ptr<OrderHandler> nextHandler;
};

// Concrete Handler: InternationalOrderHandler
class InternationalOrderHandler : public OrderHandler
{
public:
    void HandleOrder(const std::string &orderDetails) override
    {
        if (orderDetails.find("international") != std::string::npos)
        {
            std::cout << "InternationalOrderHandler is handling the order: " << orderDetails << std::endl;
        }
        else if (nextHandler != nullptr)
        {
            nextHandler->HandleOrder(orderDetails);
        }
        else
        {
            std::cout << "No handler can handle the order: " << orderDetails << std::endl;
        }
    }

    void SetNextHandler(std::shared_ptr<OrderHandler> handler) override
    {
        nextHandler = handler;
    }

private:
    std::shared_ptr<OrderHandler> nextHandler;
};

int main()
{
    // Create a chain of order handlers
    std::shared_ptr<OrderHandler> smallOrderHandler = std::make_shared<SmallOrderHandler>();
    std::shared_ptr<OrderHandler> internationalOrderHandler = std::make_shared<InternationalOrderHandler>();

    // Set up the chain
    smallOrderHandler->SetNextHandler(internationalOrderHandler);

    // Simulate processing orders
    smallOrderHandler->HandleOrder("Small domestic order");
    smallOrderHandler->HandleOrder("International order");
    smallOrderHandler->HandleOrder("Large domestic order");

    return 0;
}
