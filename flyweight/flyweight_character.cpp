#include <iostream>
#include <unordered_map>

class Character
{
public:
    virtual void Display(int pointSize) = 0;
    virtual ~Character() = default;
};

class ConcreteCharacter : public Character
{
public:
    ConcreteCharacter(char symbol) : symbol_(symbol)
    {
    }
    void Display(int pointSize) override
    {
        std::cout << "Symbol: " << symbol_ << ", Point Size: " << pointSize << '\n';
    }

private:
    char symbol_;
};

class CharacterFactory
{
public:
    Character *GetCharacter(char key)
    {
        if (characters_.count(key) == 0)
        {
            characters_[key] = new ConcreteCharacter(key);
        }
        return characters_[key];
    }

private:
    std::unordered_map<char, Character *> characters_;
};

int main()
{
    CharacterFactory *factory = new CharacterFactory();

    Character *a = factory->GetCharacter('A');
    a->Display(12);
    Character *b = factory->GetCharacter('B');
    b->Display(12);
    Character *c = factory->GetCharacter('C');
    c->Display(12);
    Character *a2 = factory->GetCharacter('A');
    a2->Display(24);

    delete factory;
    return 0;
}
