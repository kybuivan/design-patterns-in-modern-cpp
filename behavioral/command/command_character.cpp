#include <iostream>
#include <vector>

// Command interface
class Command
{
public:
    virtual ~Command()
    {
    }
    virtual void execute() = 0;
};

// Receiver class
class Character
{
public:
    void jump()
    {
        std::cout << "Character is jumping." << std::endl;
    }

    void attack()
    {
        std::cout << "Character is attacking." << std::endl;
    }
};

// Concrete command for jump
class JumpCommand : public Command
{
private:
    Character *character;

public:
    JumpCommand(Character *character) : character(character)
    {
    }

    void execute() override
    {
        character->jump();
    }
};

// Concrete command for attack
class AttackCommand : public Command
{
private:
    Character *character;

public:
    AttackCommand(Character *character) : character(character)
    {
    }

    void execute() override
    {
        character->attack();
    }
};

// Invoker class
class InputHandler
{
private:
    std::vector<Command *> commands;

public:
    void addCommand(Command *command)
    {
        commands.push_back(command);
    }

    void handleInput()
    {
        for (Command *command : commands)
        {
            command->execute();
        }
    }
};

int main()
{
    Character character;
    InputHandler inputHandler;

    // Create concrete command objects
    JumpCommand jump(&character);
    AttackCommand attack(&character);

    // Assign commands to input keys
    inputHandler.addCommand(&jump);   // Assign jump to a key
    inputHandler.addCommand(&attack); // Assign attack to another key

    // Simulate user input
    inputHandler.handleInput(); // Character jumps and attacks

    return 0;
}
