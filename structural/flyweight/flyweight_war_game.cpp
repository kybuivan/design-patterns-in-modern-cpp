#include <iostream>
#include <vector>

// Flyweight Interface
class Soldier
{
public:
    virtual void moveSoldier(int previousLocationX, int previousLocationY, int newLocationX, int newLocationY) = 0;
};

// Flyweight Implementation
class SoldierImp : public Soldier
{
public:
    void moveSoldier(int previousLocationX, int previousLocationY, int newLocationX, int newLocationY) override
    {
        // Delete soldier representation from the previous location
        // Then render soldier representation in the new location
        std::cout << "Moving soldier from (" << previousLocationX << ", " << previousLocationY << ") to (" << newLocationX << ", " << newLocationY
                  << ")\n";
    }
};

// Flyweight Factory
class SoldierFactory
{
public:
    static Soldier *getSoldier()
    {
        // This is a singleton; create the soldier if it doesn't exist
        if (!SOLDIER)
        {
            SOLDIER = new SoldierImp();
        }
        return SOLDIER;
    }

private:
    static Soldier *SOLDIER;
};

Soldier *SoldierFactory::SOLDIER = nullptr;

// Soldier Client
class SoldierClient
{
public:
    SoldierClient()
    {
        soldier = SoldierFactory::getSoldier();
    }

    void moveSoldier(int newLocationX, int newLocationY)
    {
        soldier->moveSoldier(currentLocationX, currentLocationY, newLocationX, newLocationY);
        currentLocationX = newLocationX;
        currentLocationY = newLocationY;
    }

private:
    Soldier *soldier;
    int currentLocationX = 0;
    int currentLocationY = 0;
};

int main()
{
    // Start war

    // Draw war terrain

    // Create 5 soldiers
    std::vector<SoldierClient> warSoldiers(5);

    // Move each soldier to their location (take user input)
    warSoldiers[0].moveSoldier(17, 2112);
    warSoldiers[0].moveSoldier(50, 100);
    warSoldiers[1].moveSoldier(137, 112);

    // Note that there is only one SoldierImp (flyweight Imp) for all 5 soldiers
    // SoldierClient size is small due to the small state it maintains
    // SoldierImp size might be large or might be small
    // However, we saved memory costs of creating 5 Soldier representations

    return 0;
}
