#include <iostream>

// Subsystem: Renderer
class Renderer
{
public:
    void initialize()
    {
        std::cout << "Renderer Initialized" << std::endl;
    }

    void renderFrame()
    {
        std::cout << "Rendering Game Frame" << std::endl;
    }
};

// Subsystem: Audio
class Audio
{
public:
    void initialize()
    {
        std::cout << "Audio Initialized" << std::endl;
    }

    void playSound(const std::string &sound)
    {
        std::cout << "Playing Sound: " << sound << std::endl;
    }
};

// Subsystem: Input
class Input
{
public:
    void initialize()
    {
        std::cout << "Input System Initialized" << std::endl;
    }

    bool isKeyPressed(char key)
    {
        return key == 'A'; // For demonstration, assume 'A' is pressed
    }
};

// Facade: GameFacade
class GameFacade
{
private:
    Renderer renderer;
    Audio audio;
    Input input;

public:
    void start()
    {
        renderer.initialize();
        audio.initialize();
        input.initialize();

        mainLoop();
    }

    void mainLoop()
    {
        //while (true)
        {
            if (input.isKeyPressed('A'))
            {
                audio.playSound("Gunshot.wav");
            }
            renderer.renderFrame();
        }
    }
};

int main()
{
    GameFacade game;
    game.start();
    return 0;
}
