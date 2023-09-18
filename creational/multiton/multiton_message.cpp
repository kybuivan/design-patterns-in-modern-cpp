#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class Multiton
{
private:
    // Private constructor to prevent external instantiation
    Multiton()
    {
    }

    // Static instance map
    static std::unordered_map<std::string, std::shared_ptr<Multiton>> instances;

public:
    // Function to get or create a Multiton instance by key
    static std::shared_ptr<Multiton> getInstance(const std::string &key)
    {
        // Check if an instance with the given key already exists
        if (instances.find(key) == instances.end())
        {
            // If not, create a new instance and store it in the map
            instances[key] = std::shared_ptr<Multiton>(new Multiton());
        }
        return instances[key];
    }

    // Public member function
    void showMessage()
    {
        std::cout << "Multiton instance is being used." << std::endl;
    }
};

// Static initialization for the instance map
std::unordered_map<std::string, std::shared_ptr<Multiton>> Multiton::instances;

int main()
{
    // Get or create Multiton instances by keys
    std::shared_ptr<Multiton> instance1 = Multiton::getInstance("Key1");
    std::shared_ptr<Multiton> instance2 = Multiton::getInstance("Key2");

    // Use the instances
    instance1->showMessage();
    instance2->showMessage();

    // Try to get an instance with the same key, it should return the existing instance
    std::shared_ptr<Multiton> instance3 = Multiton::getInstance("Key1");
    instance3->showMessage();

    return 0;
}
