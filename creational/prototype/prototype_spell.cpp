#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// Abstract base class for magical spells
class Spell
{
public:
    virtual std::shared_ptr<Spell> clone() const = 0;
    virtual void cast() const = 0;
    virtual ~Spell() = default;
};

// Concrete spell classes
class FireballSpell : public Spell
{
public:
    std::shared_ptr<Spell> clone() const override
    {
        return std::make_shared<FireballSpell>(*this);
    }

    void cast() const override
    {
        std::cout << "Casting Fireball Spell!" << std::endl;
    }
};

class IceBlastSpell : public Spell
{
public:
    std::shared_ptr<Spell> clone() const override
    {
        return std::make_shared<IceBlastSpell>(*this);
    }

    void cast() const override
    {
        std::cout << "Casting Ice Blast Spell!" << std::endl;
    }
};

// Prototype manager to manage spell prototypes
class SpellBook
{
private:
    std::unordered_map<std::string, std::shared_ptr<Spell>> spellPrototypes;

public:
    SpellBook()
    {
        // Initialize spell prototypes
        spellPrototypes["Fireball"] = std::make_shared<FireballSpell>();
        spellPrototypes["IceBlast"] = std::make_shared<IceBlastSpell>();
    }

    std::shared_ptr<Spell> createSpell(const std::string &type)
    {
        if (spellPrototypes.find(type) != spellPrototypes.end())
        {
            return spellPrototypes[type]->clone();
        }
        return nullptr;
    }
};

int main()
{
    SpellBook spellBook;

    // Create and cast spells
    auto fireball1 = spellBook.createSpell("Fireball");
    auto fireball2 = spellBook.createSpell("Fireball");
    auto iceBlast = spellBook.createSpell("IceBlast");

    if (fireball1 && fireball2 && iceBlast)
    {
        fireball1->cast();
        fireball2->cast();
        iceBlast->cast();
    }

    return 0;
}
