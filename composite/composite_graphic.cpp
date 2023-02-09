#include <iostream>
#include <vector>

class Graphic {
 public:
  virtual void draw() = 0;
};

class ImageEditor {
 public:
  void addGraphic(Graphic* graphic) {
    graphics_.push_back(graphic);
  }

  void draw() {
    for (auto graphic : graphics_) {
      graphic->draw();
    }
  }

 private:
  std::vector<Graphic*> graphics_;
};

class Dot : public Graphic {
 public:
  void draw() override {
    std::cout << "Drawing Dot" << std::endl;
  }
};

class CompoundGraphic : public Graphic {
 public:
  void add(Graphic* graphic) {
    graphics_.push_back(graphic);
  }

  void draw() override {
    for (auto graphic : graphics_) {
      graphic->draw();
    }
  }

 private:
  std::vector<Graphic*> graphics_;
};

class Circle : public Graphic {
 public:
  void draw() override {
    std::cout << "Drawing Circle" << std::endl;
  }
};

int main() {
  ImageEditor editor;
  CompoundGraphic compoundGraphic;
  Dot dot1, dot2;
  Circle circle;

  compoundGraphic.add(&dot1);
  compoundGraphic.add(&dot2);
  compoundGraphic.add(&circle);

  editor.addGraphic(&compoundGraphic);
  editor.draw();

  return 0;
}
