#include <iostream>
#include <vector>

// Shape class with a switch statement for calculating area
class Shape
{
public:
    enum Type
    {
        Rectangle,
        Circle
    };

    Type type;

    Shape(Type t) : type(t)
    {
    }

    double area() const
    {
        switch (type)
        {
        case Rectangle:
            return 5.0 * 4.0;
        case Circle:
            return 3.14159265358979323846 * 3.0 * 3.0;
        }
        return 0.0; // Default, should never happen
    }
};

int main()
{
    Shape rectangle(Shape::Rectangle);
    Shape circle(Shape::Circle);

    std::vector<Shape> shapes = {rectangle, circle};

    double totalArea = 0.0;
    for (const auto &shape : shapes)
    {
        totalArea += shape.area();
    }

    std::cout << "Total Area: " << totalArea << std::endl;

    return 0;
}
