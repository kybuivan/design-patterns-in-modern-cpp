#include <iostream>
#include <memory>

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
    // Declare objects of the SubsystemA and SubsystemB classes
    SubsystemA subsystemA;
    SubsystemB subsystemB;

public:
    // Declare the operation function
    void operation()
    {
        // Call the operationA and operationB functions of the SubsystemA and SubsystemB objects, respectively
        subsystemA.operationA();
        subsystemB.operationB();
    }
};

int main()
{
    // Create an object of the Facade class
    Facade facade;

    // Call the operation function of the Facade object
    facade.operation();

    return 0;
}
