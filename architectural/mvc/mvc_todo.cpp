#include <iostream>
#include <string>
#include <vector>

// Model (Task Management)
class TodoListModel
{
public:
    struct Task
    {
        std::string description;
        bool isCompleted;

        Task(const std::string &_description) : description(_description), isCompleted(false)
        {
        }
    };

private:
    std::vector<Task> tasks;

public:
    void addTask(const std::string &description)
    {
        Task task(description);
        tasks.push_back(task);
    }

    bool deleteTask(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
            tasks.erase(tasks.begin() + index);
            return true;
        }
        return false;
    }

    bool toggleTaskStatus(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
            tasks[index].isCompleted = !tasks[index].isCompleted;
            return true;
        }
        return false;
    }

    const std::vector<Task> &getTasks() const
    {
        return tasks;
    }
};

// View (Task Display)
class TodoListView
{
public:
    void displayTasks(const std::vector<TodoListModel::Task> &tasks)
    {
        std::cout << "To-Do List:\n";
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            std::cout << "[" << (tasks[i].isCompleted ? "X" : " ") << "] ";
            std::cout << i + 1 << ". " << tasks[i].description << "\n";
        }
    }
};

// Controller (Task Management)
class TodoListController
{
private:
    TodoListModel model;
    TodoListView view;

public:
    void addTask(const std::string &description)
    {
        model.addTask(description);
    }

    bool deleteTask(int index)
    {
        return model.deleteTask(index);
    }

    bool toggleTaskStatus(int index)
    {
        return model.toggleTaskStatus(index);
    }

    void displayTasks()
    {
        view.displayTasks(model.getTasks());
    }
};

int main()
{
    TodoListController controller;

    controller.addTask("Task 1");
    controller.addTask("Task 2");
    controller.addTask("Task 3");

    controller.displayTasks();

    std::cout << "\nCompleting task #2...\n";
    controller.toggleTaskStatus(1);

    std::cout << "\nDeleting task #1...\n";
    controller.deleteTask(0);

    controller.displayTasks();

    return 0;
}
