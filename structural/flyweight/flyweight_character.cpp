#include <iostream>
#include <memory>
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
    std::shared_ptr<Character> GetCharacter(char key)
    {
        auto it = characters_.find(key);
        if (it == characters_.end())
        {
            it = characters_.emplace(key, std::make_shared<ConcreteCharacter>(key)).first;
        }
        return it->second;
    }

private:
    std::unordered_map<char, std::shared_ptr<Character>> characters_;
};

int main()
{
    CharacterFactory factory;

    std::shared_ptr<Character> a = factory.GetCharacter('A');
    a->Display(12);
    std::shared_ptr<Character> b = factory.GetCharacter('B');
    b->Display(12);
    std::shared_ptr<Character> c = factory.GetCharacter('C');
    c->Display(12);
    std::shared_ptr<Character> a2 = factory.GetCharacter('A');
    a2->Display(24);

    return 0;
}
