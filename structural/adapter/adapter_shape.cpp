#include <iostream>
#include <memory>

// Target interface
class Shape
{
public:
    virtual ~Shape() = default; // Add a virtual destructor
    virtual void draw() = 0;
};

// Adaptee class
class LegacyRectangle
{
public:
    void drawRectangle()
    {
        std::cout << "Drawing rectangle using legacy code" << std::endl;
    }
};

// Adapter class
class RectangleAdapter : public Shape, private LegacyRectangle
{
public:
    void draw() override
    {
        drawRectangle();
    }
};

int main()
{
    std::unique_ptr<Shape> shape = std::make_unique<RectangleAdapter>();
    shape->draw();
    return 0;
}
