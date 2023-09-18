#include <iostream>
#include <memory>

class LazyObject
{
private:
    std::shared_ptr<int> data; // The actual object

public:
    LazyObject() : data(nullptr)
    {
    }

    // Function to access the object, creating it if it doesn't exist yet
    std::shared_ptr<int> getData()
    {
        if (!data)
        {
            // Initialize the object if it hasn't been created yet
            data = std::make_shared<int>(42);
            std::cout << "Object created." << std::endl;
        }
        return data;
    }
};

int main()
{
    LazyObject lazyObj;

    // Access the data, which will create the object
    std::shared_ptr<int> lazyData = lazyObj.getData();
    std::cout << "Data: " << *lazyData << std::endl;

    // Access the data again, which won't create a new object
    std::shared_ptr<int> lazyData2 = lazyObj.getData();
    std::cout << "Data: " << *lazyData2 << std::endl;

    return 0;
}
