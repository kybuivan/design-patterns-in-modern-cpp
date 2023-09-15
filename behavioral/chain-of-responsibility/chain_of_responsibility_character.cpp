#include <iostream>
#include <memory>
#include <string>

class PurchaseRequest
{
public:
    PurchaseRequest(const std::string &item, double amount) : item_(item), amount_(amount)
    {
    }

    const std::string &getItem() const
    {
        return item_;
    }

    double getAmount() const
    {
        return amount_;
    }

private:
    std::string item_;
    double amount_;
};

class GameCharacter
{
public:
    GameCharacter(const std::string &name, std::shared_ptr<GameCharacter> next) : name_(name), next_(next)
    {
    }

    virtual void processRequest(std::shared_ptr<PurchaseRequest> request) = 0;

    void setNext(std::shared_ptr<GameCharacter> next)
    {
        next_ = next;
    }

protected:
    std::string name_;
    std::shared_ptr<GameCharacter> next_;
};

class Elf : public GameCharacter
{
public:
    Elf(const std::string &name, std::shared_ptr<GameCharacter> next) : GameCharacter(name, next)
    {
    }

    void processRequest(std::shared_ptr<PurchaseRequest> request) override
    {
        if (request->getAmount() <= 50.0)
        {
            std::cout << name_ << " approves the purchase of " << request->getItem() << "." << std::endl;
        }
        else if (next_)
        {
            next_->processRequest(request);
        }
        else
        {
            std::cout << name_ << " cannot approve the purchase of " << request->getItem() << "." << std::endl;
        }
    }
};

class Orc : public GameCharacter
{
public:
    Orc(const std::string &name, std::shared_ptr<GameCharacter> next) : GameCharacter(name, next)
    {
    }

    void processRequest(std::shared_ptr<PurchaseRequest> request) override
    {
        if (request->getAmount() <= 100.0)
        {
            std::cout << name_ << " approves the purchase of " << request->getItem() << "." << std::endl;
        }
        else if (next_)
        {
            next_->processRequest(request);
        }
        else
        {
            std::cout << name_ << " cannot approve the purchase of " << request->getItem() << "." << std::endl;
        }
    }
};

class Wizard : public GameCharacter
{
public:
    Wizard(const std::string &name, std::shared_ptr<GameCharacter> next) : GameCharacter(name, next)
    {
    }

    void processRequest(std::shared_ptr<PurchaseRequest> request) override
    {
        std::cout << name_ << " approves the purchase of " << request->getItem() << "." << std::endl;
    }
};

int main()
{
    // Create a chain of characters: Elf -> Orc -> Wizard
    std::shared_ptr<GameCharacter> wizard = std::make_shared<Wizard>("Gandalf", nullptr);
    std::shared_ptr<GameCharacter> orc = std::make_shared<Orc>("Thrall", wizard);
    std::shared_ptr<GameCharacter> elf = std::make_shared<Elf>("Legolas", orc);

    // Process purchase requests
    std::shared_ptr<PurchaseRequest> request1 = std::make_shared<PurchaseRequest>("Magic Potion", 80.0);
    std::shared_ptr<PurchaseRequest> request2 = std::make_shared<PurchaseRequest>("Sword", 30.0);
    std::shared_ptr<PurchaseRequest> request3 = std::make_shared<PurchaseRequest>("Dragon Egg", 200.0);

    elf->processRequest(request1);
    elf->processRequest(request2);
    elf->processRequest(request3);

    return 0;
}
