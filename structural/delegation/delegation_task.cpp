#include <iostream>

// Abstract interface for the delegatee
class Delegatee
{
public:
    virtual void performTask() = 0;
};

// Concrete implementation of the delegatee
class ConcreteDelegatee : public Delegatee
{
public:
    void performTask() override
    {
        std::cout << "ConcreteDelegatee is performing the task." << std::endl;
    }
};

// Delegator class that uses delegation
class Delegator
{
private:
    Delegatee *delegatee; // Reference to the delegatee

public:
    Delegator(Delegatee *delegatee) : delegatee(delegatee)
    {
    }

    void doTask()
    {
        delegatee->performTask(); // Delegation of the task to the delegatee
    }
};

int main()
{
    ConcreteDelegatee concreteDelegatee;
    Delegator delegator(&concreteDelegatee);

    delegator.doTask(); // Delegation of the task

    return 0;
}
