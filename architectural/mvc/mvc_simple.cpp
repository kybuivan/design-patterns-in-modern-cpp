#include <iostream>
#include <string>
#include <vector>

// Model
class Model
{
private:
    std::string data;

public:
    void setData(const std::string &newData)
    {
        data = newData;
    }

    std::string getData() const
    {
        return data;
    }
};

// View
class View
{
public:
    void displayData(const std::string &data)
    {
        std::cout << "View: Displaying data - " << data << std::endl;
    }

    std::string getUserInput()
    {
        std::string input;
        std::cout << "View: Enter new data: ";
        std::cin >> input;
        return input;
    }
};

// Controller
class Controller
{
private:
    Model model;
    View view;

public:
    void run()
    {
        std::string initialData = "Default Data";
        model.setData(initialData);

        while (true)
        {
            view.displayData(model.getData());

            std::string userInput = view.getUserInput();
            model.setData(userInput);
        }
    }
};

int main()
{
    Controller controller;
    controller.run();

    return 0;
}
