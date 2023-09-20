#include <iostream>
#include <string>
#include <vector>

// Model (Drawing Canvas and Shapes)
class DrawingModel
{
private:
    std::vector<std::string> canvas;

public:
    DrawingModel(int width, int height)
    {
        canvas.resize(height, std::string(width, ' '));
    }

    const std::vector<std::string> &getCanvas() const
    {
        return canvas;
    }

    void drawLine(int x1, int y1, int x2, int y2, char brush)
    {
        // Simplified line drawing logic
        for (int y = y1; y <= y2; ++y)
        {
            for (int x = x1; x <= x2; ++x)
            {
                canvas[y][x] = brush;
            }
        }
    }

    void drawRectangle(int x, int y, int width, int height, char brush)
    {
        // Simplified rectangle drawing logic
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                canvas[y + i][x + j] = brush;
            }
        }
    }
};

// View (Drawing Canvas Renderer)
class DrawingView
{
public:
    void renderCanvas(const std::vector<std::string> &canvas)
    {
        for (const std::string &row : canvas)
        {
            std::cout << row << std::endl;
        }
    }
};

// Controller (Drawing Actions)
class DrawingController
{
private:
    DrawingModel model;
    DrawingView view;

public:
    DrawingController(int width, int height) : model(width, height)
    {
    }

    void drawLine(int x1, int y1, int x2, int y2, char brush)
    {
        model.drawLine(x1, y1, x2, y2, brush);
        view.renderCanvas(model.getCanvas());
    }

    void drawRectangle(int x, int y, int width, int height, char brush)
    {
        model.drawRectangle(x, y, width, height, brush);
        view.renderCanvas(model.getCanvas());
    }
};

int main()
{
    DrawingController controller(40, 20);

    controller.drawLine(5, 5, 35, 5, '*');
    controller.drawRectangle(10, 10, 20, 8, '#');

    return 0;
}
