#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Model
class TaskModel
{
private:
    std::vector<std::string> tasks;

public:
    void addTask(const std::string &task)
    {
        tasks.push_back(task);
    }

    void removeTask(int index)
    {
        if (index >= 0 && index < tasks.size())
        {
            tasks.erase(tasks.begin() + index);
        }
    }

    const std::vector<std::string> &getAllTasks() const
    {
        return tasks;
    }

    void saveTasksToFile(const std::string &filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (const std::string &task : tasks)
            {
                file << task << std::endl;
            }
            file.close();
        }
        else
        {
            std::cerr << "Unable to open the file: " << filename << std::endl;
        }
    }

    void loadTasksFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            tasks.clear();
            std::string task;
            while (std::getline(file, task))
            {
                tasks.push_back(task);
            }
            file.close();
        }
        else
        {
            std::cerr << "Unable to open the file: " << filename << std::endl;
        }
    }
};

// View
class TaskView
{
public:
    void showTasks(const std::vector<std::string> &tasks)
    {
        std::cout << "Tasks:" << std::endl;
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            std::cout << i + 1 << ". " << tasks[i] << std::endl;
        }
    }

    std::string getTaskInput()
    {
        std::string input;
        std::cout << "Enter a task: ";
        std::cin.ignore();
        std::getline(std::cin, input);
        return input;
    }

    int getTaskIndexToRemove()
    {
        int index;
        std::cout << "Enter the number of the task to remove (0 to cancel): ";
        std::cin >> index;
        return index;
    }
};

// Controller
class TaskController
{
private:
    TaskModel model;
    TaskView view;

public:
    void run()
    {
        model.loadTasksFromFile("tasks.txt"); // Load tasks from file at startup

        while (true)
        {
            view.showTasks(model.getAllTasks());

            std::string userInput;
            std::cout << "Options: add, remove, save, exit" << std::endl;
            std::cout << "Enter an option: ";
            std::cin >> userInput;

            if (userInput == "exit")
            {
                model.saveTasksToFile("tasks.txt"); // Save tasks to file before exiting
                break;
            }
            else if (userInput == "add")
            {
                std::string newTask = view.getTaskInput();
                model.addTask(newTask);
            }
            else if (userInput == "remove")
            {
                int index = view.getTaskIndexToRemove();
                if (index == 0)
                {
                    continue; // Cancel removal
                }
                model.removeTask(index - 1);
            }
            else if (userInput == "save")
            {
                model.saveTasksToFile("tasks.txt"); // Save tasks to file
            }
        }
    }
};

int main()
{
    TaskController controller;
    controller.run();

    return 0;
}
