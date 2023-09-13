#include <iostream>
#include <vector>

// Abstract Shape class
class Shape
{
public:
    virtual double area() const = 0;
};

// Concrete Rectangle class
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

// Concrete Circle class
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

// AreaCalculator is open for extension (new shapes can be added)
// but closed for modification (existing code doesn't change)
class AreaCalculator
{
public:
    double calculateArea(const std::vector<Shape *> &shapes) const
    {
        double totalArea = 0.0;
        for (const auto &shape : shapes)
        {
            totalArea += shape->area();
        }
        return totalArea;
    }
};

int main()
{
    Rectangle rectangle(5.0, 4.0);
    Circle circle(3.0);

    std::vector<Shape *> shapes = {&rectangle, &circle};

    AreaCalculator calculator;
    double totalArea = calculator.calculateArea(shapes);

    std::cout << "Total Area: " << totalArea << std::endl;

    return 0;
}
