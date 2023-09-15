#include <iostream>
#include <vector>

// Forward declaration of Character and its derived classes
class Character;
class Warrior;
class Wizard;

// Visitor interface
class CharacterVisitor
{
public:
    virtual void visit(Warrior &warrior) = 0;
    virtual void visit(Wizard &wizard) = 0;
};

// Element interface
class Character
{
public:
    virtual void accept(CharacterVisitor &visitor) = 0;
    virtual ~Character() = default;
};

// Concrete element: Warrior
class Warrior : public Character
{
public:
    void accept(CharacterVisitor &visitor) override
    {
        visitor.visit(*this);
    }
};

// Concrete element: Wizard
class Wizard : public Character
{
public:
    void accept(CharacterVisitor &visitor) override
    {
        visitor.visit(*this);
    }
};

// Concrete visitor: StatCalculator
class StatCalculator : public CharacterVisitor
{
public:
    void visit(Warrior &warrior) override
    {
        std::cout << "Calculating stats for Warrior." << std::endl;
        // Calculate Warrior-specific statistics
    }

    void visit(Wizard &wizard) override
    {
        std::cout << "Calculating stats for Wizard." << std::endl;
        // Calculate Wizard-specific statistics
    }
};

int main()
{
    // Create characters
    Warrior warrior;
    Wizard wizard;

    // Create a visitor
    StatCalculator calculator;

    // Accept the visitor to calculate statistics
    warrior.accept(calculator);
    wizard.accept(calculator);

    return 0;
}
