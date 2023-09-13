#include <iostream>

class Rectangle
{
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h)
    {
    }

    void setWidth(double w)
    {
        width = w;
    }

    void setHeight(double h)
    {
        height = h;
    }

    double area() const
    {
        return width * height;
    }
};

class Circle
{
private:
    double radius;

public:
    Circle(double r) : radius(r)
    {
    }

    double area() const
    {
        return 3.14159265358979323846 * radius * radius;
    }
};

void printArea(const Rectangle &rectangle)
{
    std::cout << "Rectangle Area: " << rectangle.area() << std::endl;
}

void printArea(const Circle &circle)
{
    std::cout << "Circle Area: " << circle.area() << std::endl;
}

int main()
{
    Rectangle rectangle(5.0, 4.0);
    Circle circle(3.0);

    printArea(rectangle); // Prints the area of the rectangle
    printArea(circle);    // Prints the area of the circle

    return 0;
}
