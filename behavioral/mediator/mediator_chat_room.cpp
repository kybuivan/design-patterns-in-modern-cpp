#include <iostream>
#include <string>
#include <vector>

// Participant (Colleague) interface
class Participant
{
public:
    virtual void sendMessage(const std::string &message) = 0;
    virtual void receiveMessage(const std::string &message) = 0;
};

class Chatroom
{
public:
    virtual void sendMessage(const std::string &message, Participant *sender) = 0;
};

// ConcreteColleague: HumanParticipant
class HumanParticipant : public Participant
{
private:
    std::string name;
    Chatroom *chatroom;

public:
    HumanParticipant(const std::string &name, Chatroom *chatroom) : name(name), chatroom(chatroom)
    {
    }

    void sendMessage(const std::string &message) override
    {
        std::cout << name << " sends: " << message << std::endl;
        chatroom->sendMessage(message, this);
    }

    void receiveMessage(const std::string &message) override
    {
        std::cout << name << " receives: " << message << std::endl;
    }
};

// ConcreteColleague: Bot
class Bot : public Participant
{
private:
    std::string name;
    Chatroom *chatroom;

public:
    Bot(const std::string &name, Chatroom *chatroom) : name(name), chatroom(chatroom)
    {
    }

    void sendMessage(const std::string &message) override
    {
        std::cout << name << " sends: " << message << std::endl;
        chatroom->sendMessage(message, this);
    }

    void receiveMessage(const std::string &message) override
    {
        std::cout << name << " receives: " << message << std::endl;
    }
};

// ConcreteMediator: ChatroomImpl
class ChatroomImpl : public Chatroom
{
private:
    std::vector<Participant *> participants;

public:
    void addParticipant(Participant *participant)
    {
        participants.push_back(participant);
    }

    void sendMessage(const std::string &message, Participant *sender) override
    {
        for (auto participant : participants)
        {
            if (participant != sender)
            {
                participant->receiveMessage(message);
            }
        }
    }
};

int main()
{
    ChatroomImpl chatroom;

    HumanParticipant alice("Alice", &chatroom);
    Bot chatbot("ChatBot", &chatroom);
    HumanParticipant bob("Bob", &chatroom);

    chatroom.addParticipant(&alice);
    chatroom.addParticipant(&chatbot);
    chatroom.addParticipant(&bob);

    alice.sendMessage("Hello, everyone!");
    chatbot.sendMessage("Hi, there!");
    bob.sendMessage("Nice to meet you all.");

    return 0;
}
