#include <iostream>

// Abstract class representing a shape
class Shape
{
public:
    virtual void draw() = 0;
};

// Concrete class representing a real shape (e.g., Circle)
class Circle : public Shape
{
public:
    void draw() override
    {
        std::cout << "Drawing a Circle." << std::endl;
    }
};

// Null Object class for cases where no shape is available
class NullShape : public Shape
{
public:
    void draw() override
    {
        // Do nothing (no-op)
    }
};

int main()
{
    // Create a real Circle object
    Circle circle;

    // Create a NullShape object to represent a missing shape
    NullShape nullShape;

    // Draw the real Circle and the NullShape
    circle.draw();
    nullShape.draw(); // This does nothing

    return 0;
}
