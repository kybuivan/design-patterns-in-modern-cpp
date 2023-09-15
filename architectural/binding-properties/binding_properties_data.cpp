#include <functional>
#include <iostream>
#include <string>
#include <vector>

class PropertyObserver
{
public:
    virtual void update(int new_value) = 0;
};

class DataProperty
{
public:
    DataProperty(int value) : value_(value)
    {
    }

    int getValue() const
    {
        return value_;
    }

    void setValue(int new_value)
    {
        if (new_value != value_)
        {
            value_ = new_value;
            notify(); // Notify bound UI elements of the value change
        }
    }

    void bind(PropertyObserver &observer)
    {
        bound_observers_.push_back(&observer);
    }

    void notify()
    {
        for (auto &observer : bound_observers_)
        {
            observer->update(value_);
        }
    }

private:
    int value_;
    std::vector<PropertyObserver *> bound_observers_;
};

class Label : public PropertyObserver
{
public:
    Label(const std::string &text) : text_(text)
    {
    }

    void update(int new_value) override
    {
        std::cout << "Label updated with value: " << new_value << std::endl;
    }

private:
    std::string text_;
};

class Button : public PropertyObserver
{
public:
    Button(const std::string &label) : label_(label)
    {
    }

    void update(int new_value) override
    {
        std::cout << "Button updated with value: " << new_value << std::endl;
    }

    void click()
    {
        std::cout << "Button clicked!" << std::endl;
    }

private:
    std::string label_;
};

int main()
{
    DataProperty data(42); // Initial data property value

    Label label("Value: ");
    Button button("Increment");

    // Bind UI elements to the data property
    data.bind(label);
    data.bind(button);

    // Simulate changes in the data property
    data.setValue(50);

    // Simulate a button click, which changes the data property
    button.click();

    return 0;
}
