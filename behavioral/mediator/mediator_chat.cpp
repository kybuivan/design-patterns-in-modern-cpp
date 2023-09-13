#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IUser;

// Abstract Mediator
class IMediator
{
public:
    virtual void addUser(std::shared_ptr<IUser> user) = 0;
    virtual void sendMessage(const std::string &message, std::shared_ptr<IUser> sender) = 0;
};

// Abstract Colleague
class IUser : public std::enable_shared_from_this<IUser>
{
public:
    IUser(const std::string &name, std::shared_ptr<IMediator> mediator) : name(name), mediator(mediator)
    {
    }

    virtual void sendMessage(const std::string &message) = 0;
    virtual void receiveMessage(const std::string &message) = 0;

    std::string getName() const
    {
        return name;
    }

protected:
    std::shared_ptr<IMediator> mediator;
    std::string name;
};

// Concrete Mediator
class ChatMediator : public IMediator
{
public:
    void addUser(std::shared_ptr<IUser> user) override
    {
        users.push_back(user);
    }

    void sendMessage(const std::string &message, std::shared_ptr<IUser> sender) override
    {
        for (const auto &user : users)
        {
            if (user != sender)
            {
                user->receiveMessage(sender->getName() + ": " + message);
            }
        }
    }

private:
    std::vector<std::shared_ptr<IUser>> users;
};

// Concrete Colleague
class ChatUser : public IUser
{
public:
    ChatUser(const std::string &name, std::shared_ptr<IMediator> mediator) : IUser(name, mediator)
    {
    }

    void sendMessage(const std::string &message) override
    {
        mediator->sendMessage(message, shared_from_this());
    }

    void receiveMessage(const std::string &message) override
    {
        std::cout << name << " received: " << message << std::endl;
    }
};

int main()
{
    // Create a mediator
    auto mediator = std::make_shared<ChatMediator>();

    // Create users and add them to the mediator
    auto user1 = std::make_shared<ChatUser>("Alice", mediator);
    auto user2 = std::make_shared<ChatUser>("Bob", mediator);
    auto user3 = std::make_shared<ChatUser>("Charlie", mediator);

    mediator->addUser(user1);
    mediator->addUser(user2);
    mediator->addUser(user3);

    // Send messages through the mediator
    user1->sendMessage("Hello, everyone!");
    user2->sendMessage("Hi, Alice!");
    user3->sendMessage("Hey there!");

    return 0;
}
