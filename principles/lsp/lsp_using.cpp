#include <iostream>

// Base class representing a geometric shape
class Shape
{
public:
    virtual double area() const = 0;
};

// Derived class: Rectangle
class Rectangle : public Shape
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h)
    {
    }

    double area() const override
    {
        return width * height;
    }
};

// Derived class: Circle
class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r) : radius(r)
    {
    }

    double area() const override
    {
        return 3.14159265358979323846 * radius * radius;
    }
};

// Function that calculates and prints the area of a shape
void printArea(const Shape &shape)
{
    std::cout << "Area: " << shape.area() << std::endl;
}

int main()
{
    Rectangle rectangle(5.0, 4.0);
    Circle circle(3.0);

    printArea(rectangle); // Prints the area of the rectangle
    printArea(circle);    // Prints the area of the circle

    return 0;
}
