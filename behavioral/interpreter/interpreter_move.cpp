#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Context: Represents the game world or state.
class GameContext
{
public:
    int playerX = 0;
    int playerY = 0;

    void movePlayer(int deltaX, int deltaY)
    {
        playerX += deltaX;
        playerY += deltaY;
    }
};

// Abstract Expression
class CommandExpression
{
public:
    virtual void interpret(GameContext &context) = 0;
    virtual ~CommandExpression()
    {
    }
};

// Terminal Expression: Represents a single movement command.
class MoveExpression : public CommandExpression
{
private:
    int deltaX;
    int deltaY;

public:
    MoveExpression(int x, int y) : deltaX(x), deltaY(y)
    {
    }

    void interpret(GameContext &context) override
    {
        context.movePlayer(deltaX, deltaY);
        std::cout << "Player moved (" << deltaX << ", " << deltaY << "). Current position: (" << context.playerX << ", " << context.playerY << ")"
                  << std::endl;
    }
};

// Non-terminal Expression: Represents a sequence of movement commands.
class SequenceExpression : public CommandExpression
{
private:
    std::vector<std::shared_ptr<CommandExpression>> commands;

public:
    void addCommand(std::shared_ptr<CommandExpression> command)
    {
        commands.push_back(command);
    }

    void interpret(GameContext &context) override
    {
        for (const auto &command : commands)
        {
            command->interpret(context);
        }
    }
};

int main()
{
    GameContext context;

    // Define a sequence of movements: (1, 0) -> (0, 1) -> (2, -1)
    std::shared_ptr<SequenceExpression> sequence = std::make_shared<SequenceExpression>();
    sequence->addCommand(std::make_shared<MoveExpression>(1, 0));
    sequence->addCommand(std::make_shared<MoveExpression>(0, 1));
    sequence->addCommand(std::make_shared<MoveExpression>(2, -1));

    // Interpret the sequence of commands in the game context.
    sequence->interpret(context);

    return 0;
}
