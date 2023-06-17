#include <iostream>
#include <memory>
#include <string>

// Abstract component class
class Notifier
{
public:
    virtual ~Notifier() = default;
    virtual void send(const std::string &message) = 0;
};

// Concrete component class
class EmailNotifier : public Notifier
{
public:
    void send(const std::string &message) override
    {
        std::cout << "Sending email: " << message << std::endl;
    }
};

// Abstract decorator class
class NotifierDecorator : public Notifier
{
protected:
    std::unique_ptr<Notifier> notifier;

public:
    NotifierDecorator(std::unique_ptr<Notifier> notifier) : notifier(std::move(notifier))
    {
    }

    void send(const std::string &message) override
    {
        notifier->send(message);
    }
};

// Concrete decorator class
class SMSNotifier : public NotifierDecorator
{
public:
    SMSNotifier(std::unique_ptr<Notifier> notifier) : NotifierDecorator(std::move(notifier))
    {
    }

    void send(const std::string &message) override
    {
        std::cout << "Sending SMS: " << message << std::endl;
        NotifierDecorator::send(message);
    }
};

// Concrete decorator class
class SlackNotifier : public NotifierDecorator
{
public:
    SlackNotifier(std::unique_ptr<Notifier> notifier) : NotifierDecorator(std::move(notifier))
    {
    }

    void send(const std::string &message) override
    {
        std::cout << "Sending Slack message: " << message << std::endl;
        NotifierDecorator::send(message);
    }
};

int main()
{
    // Initialize a basic email notifier
    std::unique_ptr<Notifier> email_notifier = std::make_unique<EmailNotifier>();
    // Decorate the email notifier with SMS and Slack notifiers
    std::unique_ptr<Notifier> notifier =
        std::make_unique<SMSNotifier>(std::make_unique<SlackNotifier>(std::move(email_notifier)));
    notifier->send("Important message");

    return 0;
}
