#include <iostream>
#include <string>

// Abstract component class
class Notifier
{
public:
    virtual void send(std::string message) = 0;
};

// Concrete component class
class EmailNotifier : public Notifier
{
public:
    void send(std::string message) override
    {
        std::cout << "Sending email: " << message << std::endl;
    }
};

// Abstract decorator class
class NotifierDecorator : public Notifier
{
protected:
    Notifier *notifier_;

public:
    NotifierDecorator(Notifier *notifier) : notifier_(notifier)
    {
    }
    void send(std::string message) override
    {
        notifier_->send(message);
    }
};

// Concrete decorator class
class SMSNotifier : public NotifierDecorator
{
public:
    SMSNotifier(Notifier *notifier) : NotifierDecorator(notifier)
    {
    }
    void send(std::string message) override
    {
        std::cout << "Sending SMS: " << message << std::endl;
        notifier_->send(message);
    }
};

// Concrete decorator class
class SlackNotifier : public NotifierDecorator
{
public:
    SlackNotifier(Notifier *notifier) : NotifierDecorator(notifier)
    {
    }
    void send(std::string message) override
    {
        std::cout << "Sending Slack message: " << message << std::endl;
        notifier_->send(message);
    }
};

int main()
{
    // Initialize a basic email notifier
    Notifier *email_notifier = new EmailNotifier();
    // Decorate the email notifier with SMS and Slack notifiers
    Notifier *notifier = new SMSNotifier(new SlackNotifier(email_notifier));
    notifier->send("Important message");
    return 0;
}
