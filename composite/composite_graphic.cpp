#include <iostream>
#include <memory>
#include <vector>

class Graphic
{
public:
    virtual void draw() = 0;
};

class ImageEditor
{
public:
    void addGraphic(std::shared_ptr<Graphic> graphic)
    {
        graphics_.push_back(graphic);
    }

    void draw()
    {
        for (const auto &graphic : graphics_)
        {
            graphic->draw();
        }
    }

private:
    std::vector<std::shared_ptr<Graphic>> graphics_;
};

class Dot : public Graphic
{
public:
    void draw() override
    {
        std::cout << "Drawing Dot" << std::endl;
    }
};

class CompoundGraphic : public Graphic
{
public:
    void add(std::shared_ptr<Graphic> graphic)
    {
        graphics_.push_back(graphic);
    }

    void draw() override
    {
        for (const auto &graphic : graphics_)
        {
            graphic->draw();
        }
    }

private:
    std::vector<std::shared_ptr<Graphic>> graphics_;
};

class Circle : public Graphic
{
public:
    void draw() override
    {
        std::cout << "Drawing Circle" << std::endl;
    }
};

int main()
{
    ImageEditor editor;
    std::shared_ptr<CompoundGraphic> compoundGraphic = std::make_shared<CompoundGraphic>();
    std::shared_ptr<Dot> dot1 = std::make_shared<Dot>();
    std::shared_ptr<Dot> dot2 = std::make_shared<Dot>();
    std::shared_ptr<Circle> circle = std::make_shared<Circle>();

    compoundGraphic->add(dot1);
    compoundGraphic->add(dot2);
    compoundGraphic->add(circle);

    editor.addGraphic(compoundGraphic);
    editor.draw();

    return 0;
}
