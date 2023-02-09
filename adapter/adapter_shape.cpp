#include <iostream>

// Target interface
class Shape {
public:
    virtual void draw() = 0;
};

// Adaptee class
class LegacyRectangle {
public:
    void drawRectangle() {
        std::cout << "Drawing rectangle using legacy code" << std::endl;
    }
};

// Adapter class
class RectangleAdapter : public Shape, private LegacyRectangle {
public:
    void draw() override {
        drawRectangle();
    }
};

int main() {
    Shape* shape = new RectangleAdapter();
    shape->draw();
    delete shape;
    return 0;
}
