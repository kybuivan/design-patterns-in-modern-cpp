#include <iostream>
#include <string>

// Base class representing a simple shape
class Shape
{
public:
    virtual void draw() const = 0;
};

// Concrete implementation of a Circle
class Circle : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing a Circle" << std::endl;
    }
};

// Concrete implementation of a Square
class Square : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing a Square" << std::endl;
    }
};

// Extension object for adding colors to shapes
class ColorExtension
{
public:
    explicit ColorExtension(const std::string &color) : color_(color)
    {
    }

    void setColor(const std::string &color)
    {
        color_ = color;
    }

    void drawWithColor(const Shape &shape) const
    {
        std::cout << "Drawing a " << color_ << " " << typeid(shape).name() << std::endl;
        shape.draw();
    }

private:
    std::string color_;
};

int main()
{
    Circle circle;
    Square square;

    ColorExtension redCircle("Red");
    ColorExtension blueSquare("Blue");

    redCircle.drawWithColor(circle);  // Drawing a Red Circle
    blueSquare.drawWithColor(square); // Drawing a Blue Square

    redCircle.setColor("Green");
    redCircle.drawWithColor(circle); // Drawing a Green Circle

    return 0;
}
