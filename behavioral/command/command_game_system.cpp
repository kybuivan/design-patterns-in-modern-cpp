#include <iostream>
#include <string>
#include <vector>

// Receiver: Game System
class GameSystem
{
public:
    void startGame()
    {
        std::cout << "Game started!" << std::endl;
    }

    void saveGame()
    {
        std::cout << "Game saved!" << std::endl;
    }

    void loadGame()
    {
        std::cout << "Game loaded!" << std::endl;
    }

    void exitGame()
    {
        std::cout << "Exiting the game..." << std::endl;
    }
};

// Command Interface
class Command
{
public:
    virtual ~Command()
    {
    }
    virtual void execute() = 0;
};

// Concrete Commands
class StartCommand : public Command
{
private:
    GameSystem &game;

public:
    StartCommand(GameSystem &game) : game(game)
    {
    }

    void execute() override
    {
        game.startGame();
    }
};

class SaveCommand : public Command
{
private:
    GameSystem &game;

public:
    SaveCommand(GameSystem &game) : game(game)
    {
    }

    void execute() override
    {
        game.saveGame();
    }
};

class LoadCommand : public Command
{
private:
    GameSystem &game;

public:
    LoadCommand(GameSystem &game) : game(game)
    {
    }

    void execute() override
    {
        game.loadGame();
    }
};

class ExitCommand : public Command
{
private:
    GameSystem &game;

public:
    ExitCommand(GameSystem &game) : game(game)
    {
    }

    void execute() override
    {
        game.exitGame();
    }
};

// GUI Button
class Button
{
private:
    Command *command;
    std::string label;

public:
    Button(Command *command, const std::string &label) : command(command), label(label)
    {
    }

    void click()
    {
        command->execute();
    }

    std::string getLabel()
    {
        return label;
    }
};

// GUI
class GUI
{
private:
    std::vector<Button *> buttons;

public:
    void addButton(Button *button)
    {
        buttons.push_back(button);
    }

    void render()
    {
        std::cout << "Game GUI:" << std::endl;
        for (Button *button : buttons)
        {
            std::cout << " - " << button->getLabel() << std::endl;
        }
    }
};

int main()
{
    GameSystem game;
    GUI gui;

    // Create commands
    StartCommand start(game);
    SaveCommand save(game);
    LoadCommand load(game);
    ExitCommand exit(game);

    // Create buttons with associated commands
    Button startButton(&start, "Start Game");
    Button saveButton(&save, "Save Game");
    Button loadButton(&load, "Load Game");
    Button exitButton(&exit, "Exit Game");

    // Add buttons to the GUI
    gui.addButton(&startButton);
    gui.addButton(&saveButton);
    gui.addButton(&loadButton);
    gui.addButton(&exitButton);

    // Render and interact with the GUI
    gui.render();

    std::cout << "User clicks buttons:" << std::endl;
    startButton.click();
    saveButton.click();
    loadButton.click();
    exitButton.click();

    return 0;
}
