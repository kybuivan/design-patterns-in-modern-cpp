#include <iostream>
#include <memory>
#include <vector>

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class CutCommand : public Command
{
public:
    void execute() override
    {
        std::cout << "Cutting..." << std::endl;
    }
};

class CopyCommand : public Command
{
public:
    void execute() override
    {
        std::cout << "Copying..." << std::endl;
    }
};

class PasteCommand : public Command
{
public:
    void execute() override
    {
        std::cout << "Pasting..." << std::endl;
    }
};

class UndoCommand : public Command
{
public:
    void execute() override
    {
        std::cout << "Undoing..." << std::endl;
    }
};

class Button
{
public:
    Button(std::shared_ptr<Command> command) : command_(command)
    {
    }
    void click()
    {
        command_->execute();
    }

private:
    std::shared_ptr<Command> command_;
};

class Shortcut
{
public:
    Shortcut(std::shared_ptr<Command> command) : command_(command)
    {
    }
    void press()
    {
        command_->execute();
    }

private:
    std::shared_ptr<Command> command_;
};

class Editor
{
public:
    Editor()
    {
        buttons_.push_back(std::make_shared<Button>(std::make_shared<CutCommand>()));
        buttons_.push_back(std::make_shared<Button>(std::make_shared<CopyCommand>()));
        buttons_.push_back(std::make_shared<Button>(std::make_shared<PasteCommand>()));
        buttons_.push_back(std::make_shared<Button>(std::make_shared<UndoCommand>()));

        shortcuts_.push_back(std::make_shared<Shortcut>(std::make_shared<CutCommand>()));
        shortcuts_.push_back(std::make_shared<Shortcut>(std::make_shared<CopyCommand>()));
        shortcuts_.push_back(std::make_shared<Shortcut>(std::make_shared<PasteCommand>()));
        shortcuts_.push_back(std::make_shared<Shortcut>(std::make_shared<UndoCommand>()));
    }
    void run()
    {
        for (const auto &button : buttons_)
        {
            button->click();
        }
        for (const auto &shortcut : shortcuts_)
        {
            shortcut->press();
        }
    }

private:
    std::vector<std::shared_ptr<Button>> buttons_;
    std::vector<std::shared_ptr<Shortcut>> shortcuts_;
};

class Application
{
public:
    Application()
    {
        editor_ = std::make_shared<Editor>();
    }
    void run()
    {
        editor_->run();
    }

private:
    std::shared_ptr<Editor> editor_;
};

int main()
{
    Application app;
    app.run();
}
