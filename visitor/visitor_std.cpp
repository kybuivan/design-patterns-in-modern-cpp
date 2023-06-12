#include <iostream>
#include <memory>
#include <variant>
#include <vector>

class Circle
{
public:
    explicit Circle(double radius) : radius_(radius)
    {
        /* Checking that the given radius is valid */
    }

    double radius() const
    {
        return radius_;
    }

private:
    double radius_;
};

class Square
{
public:
    explicit Square(double side) : side_(side)
    {
        /* Checking that the given side length is valid */
    }

    double side() const
    {
        return side_;
    }

private:
    double side_;
};

struct Draw
{
    void operator()(Circle const &c /*, ...*/) const
    {
        std::cout << "Drawing a circle with radius: " << c.radius() << std::endl;
    }

    void operator()(Square const &s /*, ...*/) const
    {
        std::cout << "Drawing a square with side length: " << s.side() << std::endl;
    }

    // Possibly more visit() functions, one for each concrete shape
};

using Shape = std::variant<Circle, Square>;
using Shapes = std::vector<Shape>;
void drawAllShapes(Shapes const &shapes)
{
    for (auto const &shape : shapes)
    {
        std::visit(Draw{}, shape);
    }
}

int main()
{

    // Creating some shapes
    Shapes shapes{};
    shapes.emplace_back(Circle(2.3));
    shapes.emplace_back(Square(1.2));
    shapes.emplace_back(Circle(4.1));

    // Drawing all shapes
    drawAllShapes(shapes);

    return 0;
}
