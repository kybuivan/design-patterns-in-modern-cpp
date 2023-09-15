#include <iostream>
#include <string>
#include <vector>

// Forward declarations
class Character;
class Item;
class Location;

// Abstract Visitor
class Visitor
{
public:
    virtual void visit(Character &character) = 0;
    virtual void visit(Item &item) = 0;
    virtual void visit(Location &location) = 0;
    virtual ~Visitor() = default;
};

// Element interface
class Element
{
public:
    virtual void accept(Visitor &visitor) = 0;
    virtual ~Element() = default;
};

// Concrete element: Character
class Character : public Element
{
public:
    std::string name;
    int health;

    Character(const std::string &n, int h) : name(n), health(h)
    {
    }

    void accept(Visitor &visitor) override
    {
        visitor.visit(*this);
    }
};

// Concrete element: Item
class Item : public Element
{
public:
    std::string name;

    Item(const std::string &n) : name(n)
    {
    }

    void accept(Visitor &visitor) override
    {
        visitor.visit(*this);
    }
};

// Concrete element: Location
class Location : public Element
{
public:
    std::string name;

    Location(const std::string &n) : name(n)
    {
    }

    void accept(Visitor &visitor) override
    {
        visitor.visit(*this);
    }
};

// Concrete Visitor: CombatVisitor
class CombatVisitor : public Visitor
{
public:
    void visit(Character &character) override
    {
        std::cout << "Combat: " << character.name << " fights." << std::endl;
    }

    void visit(Item &item) override
    {
        std::cout << "Combat: Cannot use " << item.name << " in battle." << std::endl;
    }

    void visit(Location &location) override
    {
        std::cout << "Combat: Exploring " << location.name << "." << std::endl;
    }
};

// Concrete Visitor: QuestVisitor
class QuestVisitor : public Visitor
{
public:
    void visit(Character &character) override
    {
        std::cout << "Quest: " << character.name << " provides a quest." << std::endl;
    }

    void visit(Item &item) override
    {
        std::cout << "Quest: " << item.name << " is a quest item." << std::endl;
    }

    void visit(Location &location) override
    {
        std::cout << "Quest: " << location.name << " is a quest location." << std::endl;
    }
};

// Concrete Visitor: TradeVisitor
class TradeVisitor : public Visitor
{
public:
    void visit(Character &character) override
    {
        std::cout << "Trade: " << character.name << " buys/sells items." << std::endl;
    }

    void visit(Item &item) override
    {
        std::cout << "Trade: " << item.name << " is available for trade." << std::endl;
    }

    void visit(Location &location) override
    {
        std::cout << "Trade: " << location.name << " is a trading hub." << std::endl;
    }
};

int main()
{
    Character player("Hero", 100);
    Item sword("Sword");
    Location village("Village");

    CombatVisitor combatVisitor;
    QuestVisitor questVisitor;
    TradeVisitor tradeVisitor;

    // Simulate different interactions
    player.accept(combatVisitor);
    sword.accept(combatVisitor);
    village.accept(combatVisitor);

    std::cout << std::endl;

    player.accept(questVisitor);
    sword.accept(questVisitor);
    village.accept(questVisitor);

    std::cout << std::endl;

    player.accept(tradeVisitor);
    sword.accept(tradeVisitor);
    village.accept(tradeVisitor);

    return 0;
}
