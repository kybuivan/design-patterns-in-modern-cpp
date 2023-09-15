#include <iostream>
#include <string>

class Request
{
public:
    Request(const std::string &type) : type_(type)
    {
    }

    const std::string &getType() const
    {
        return type_;
    }

private:
    std::string type_;
};

class Handler
{
public:
    Handler(Handler *successor = nullptr) : successor_(successor)
    {
    }

    virtual void handleRequest(const Request &request)
    {
        if (successor_)
        {
            successor_->handleRequest(request);
        }
        else
        {
            std::cout << "Request unhandled." << std::endl;
        }
    }

    void setSuccessor(Handler *successor)
    {
        successor_ = successor;
    }

private:
    Handler *successor_;
};

class ConcreteHandlerA : public Handler
{
public:
    void handleRequest(const Request &request) override
    {
        if (request.getType() == "TypeA")
        {
            std::cout << "ConcreteHandlerA handles the request of type: " << request.getType() << std::endl;
        }
        else
        {
            Handler::handleRequest(request);
        }
    }
};

class ConcreteHandlerB : public Handler
{
public:
    void handleRequest(const Request &request) override
    {
        if (request.getType() == "TypeB")
        {
            std::cout << "ConcreteHandlerB handles the request of type: " << request.getType() << std::endl;
        }
        else
        {
            Handler::handleRequest(request);
        }
    }
};

class ConcreteHandlerC : public Handler
{
public:
    void handleRequest(const Request &request) override
    {
        if (request.getType() == "TypeC")
        {
            std::cout << "ConcreteHandlerC handles the request of type: " << request.getType() << std::endl;
        }
        else
        {
            Handler::handleRequest(request);
        }
    }
};

int main()
{
    // Create a chain of handlers
    ConcreteHandlerA handlerA;
    ConcreteHandlerB handlerB;
    ConcreteHandlerC handlerC;

    handlerA.setSuccessor(&handlerB);
    handlerB.setSuccessor(&handlerC);

    // Create some requests
    Request request1("TypeA");
    Request request2("TypeB");
    Request request3("TypeC");
    Request request4("TypeD");

    // Process the requests
    handlerA.handleRequest(request1);
    handlerA.handleRequest(request2);
    handlerA.handleRequest(request3);
    handlerA.handleRequest(request4);

    return 0;
}
