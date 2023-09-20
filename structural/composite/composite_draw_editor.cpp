#include <iostream>
#include <memory>
#include <vector>

// Shape is the Component interface
class Shape : public std::enable_shared_from_this<Shape>
{
public:
    virtual ~Shape() = default;
    virtual void renderShapeToScreen() = 0;
    virtual std::vector<std::shared_ptr<Shape>> explodeShape() = 0;
};

// Line is a basic shape that does not support adding shapes
class Line : public Shape
{
public:
    Line(int point1X, int point1Y, int point2X, int point2Y) : point1X_(point1X), point1Y_(point1Y), point2X_(point2X), point2Y_(point2Y)
    {
    }

    void renderShapeToScreen() override
    {
        std::cout << "Drawing a Line from (" << point1X_ << "," << point1Y_ << ") to (" << point2X_ << "," << point2Y_ << ")\n";
    }

    std::vector<std::shared_ptr<Shape>> explodeShape() override
    {
        std::vector<std::shared_ptr<Shape>> shapeParts = {shared_from_this()};
        return shapeParts;
    }

private:
    int point1X_;
    int point1Y_;
    int point2X_;
    int point2Y_;
};

// Rectangle is a composite
class Rectangle : public Shape
{
public:
    Rectangle()
    {
        rectangleEdges_.emplace_back(std::make_shared<Line>(-1, -1, 1, -1));
        rectangleEdges_.emplace_back(std::make_shared<Line>(-1, 1, 1, 1));
        rectangleEdges_.emplace_back(std::make_shared<Line>(-1, -1, -1, 1));
        rectangleEdges_.emplace_back(std::make_shared<Line>(1, -1, 1, 1));
    }

    void renderShapeToScreen() override
    {
        for (const auto &s : rectangleEdges_)
        {
            s->renderShapeToScreen();
        }
    }

    std::vector<std::shared_ptr<Shape>> explodeShape() override
    {
        return rectangleEdges_;
    }

private:
    std::vector<std::shared_ptr<Shape>> rectangleEdges_;
};

// ComplexShape is a composite supporting creation of more complex shapes
class ComplexShape : public Shape
{
public:
    void addToShape(std::shared_ptr<Shape> shapeToAddToCurrentShape)
    {
        shapeList_.emplace_back(shapeToAddToCurrentShape);
    }

    void renderShapeToScreen() override
    {
        for (const auto &s : shapeList_)
        {
            s->renderShapeToScreen();
        }
    }

    std::vector<std::shared_ptr<Shape>> explodeShape() override
    {
        return shapeList_;
    }

private:
    std::vector<std::shared_ptr<Shape>> shapeList_;
};

int main()
{
    std::vector<std::shared_ptr<Shape>> allShapesInSoftware;

    // Create a line shape
    allShapesInSoftware.emplace_back(std::make_shared<Line>(0, 0, 1, 1));

    // Create a rectangle shape
    allShapesInSoftware.emplace_back(std::make_shared<Rectangle>());

    // Create a complex shape
    auto complexShape = std::make_shared<ComplexShape>();
    complexShape->addToShape(std::make_shared<Rectangle>());
    complexShape->addToShape(std::make_shared<Line>(0, 0, 1, 1));
    allShapesInSoftware.emplace_back(complexShape);

    // Create a more complex shape
    auto veryComplexShape = std::make_shared<ComplexShape>();
    veryComplexShape->addToShape(complexShape);
    veryComplexShape->addToShape(std::make_shared<Line>(0, 0, 1, 1));
    allShapesInSoftware.emplace_back(veryComplexShape);

    // Render graphics for all shapes
    for (const auto &s : allShapesInSoftware)
    {
        s->renderShapeToScreen();
    }

    // Explode any object
    // Despite whether the shape is simple or complex
    std::vector<std::shared_ptr<Shape>> arrayOfShapes = allShapesInSoftware[0]->explodeShape();

    return 0;
}
