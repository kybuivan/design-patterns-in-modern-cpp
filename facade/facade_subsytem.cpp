#include <iostream>

// Declare the SubsystemA class
class SubsystemA
{
public:
    // Declare the operationA function
    void operationA()
    {
        std::cout << "Operation A in Subsystem A" << std::endl;
    }
};

// Declare the SubsystemB class
class SubsystemB
{
public:
    // Declare the operationB function
    void operationB()
    {
        std::cout << "Operation B in Subsystem B" << std::endl;
    }
};

// Declare the Facade class
class Facade
{
private:
    // Declare pointers to objects of the SubsystemA and SubsystemB classes
    SubsystemA *subsystemA;
    SubsystemB *subsystemB;

public:
    // Constructor for the Facade class
    Facade()
    {
        // Create objects of the SubsystemA and SubsystemB classes
        subsystemA = new SubsystemA();
        subsystemB = new SubsystemB();
    }

    // Declare the operation function
    void operation()
    {
        // Call the operationA and operationB functions of the SubsystemA and SubsystemB objects, respectively
        subsystemA->operationA();
        subsystemB->operationB();
    }
};

int main()
{
    // Create an object of the Facade class
    Facade *facade = new Facade();

    // Call the operation function of the Facade object
    facade->operation();

    return 0;
}
