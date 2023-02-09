#include <iostream>
#include <string>
#include <vector>

class Email
{
private:
    std::string from;
    std::vector<std::string> to;
    std::string subject;
    std::string body;

public:
    Email(const std::string& from, const std::vector<std::string>& to, const std::string& subject, const std::string& body)
        : from(from), to(to), subject(subject), body(body)
    {
    }

    void show()
    {
        std::cout << "From: " << from << std::endl;
        std::cout << "To: ";
        for (const auto& recipient : to)
        {
            std::cout << recipient << " ";
        }
        std::cout << std::endl;
        std::cout << "Subject: " << subject << std::endl;
        std::cout << "Body: " << body << std::endl;
    }
};

class EmailBuilder
{
private:
    std::string from;
    std::vector<std::string> to;
    std::string subject;
    std::string body;

public:
    EmailBuilder& setFrom(const std::string& from)
    {
        this->from = from;
        return *this;
    }

    EmailBuilder& addTo(const std::string& to)
    {
        this->to.push_back(to);
        return *this;
    }

    EmailBuilder& setSubject(const std::string& subject)
    {
        this->subject = subject;
        return *this;
    }

    EmailBuilder& setBody(const std::string& body)
    {
        this->body = body;
        return *this;
    }

    Email build()
    {
        return Email(from, to, subject, body);
    }
};

class MailService
{
public:
    void sendEmail(Email& email)
    {
        std::cout << "Sending email..." << std::endl;
        email.show();
    }
};

int main()
{
    MailService mailService;
    Email email = EmailBuilder()
        .setFrom("sender@example.com")
        .addTo("recipient1@example.com")
        .addTo("recipient2@example.com")
        .setSubject("Hello")
        .setBody("How are you?")
        .build();

    mailService.sendEmail(email);

    return 0;
}