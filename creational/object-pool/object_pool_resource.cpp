#include <iostream>
#include <memory>
#include <vector>

// Reusable Object
class Resource
{
public:
    void operation()
    {
        std::cout << "Performing an operation with Resource." << std::endl;
    }
};

// Object Pool
class ObjectPool
{
public:
    ObjectPool(int poolSize)
    {
        for (int i = 0; i < poolSize; ++i)
        {
            resources.push_back(std::make_shared<Resource>());
        }
    }

    std::shared_ptr<Resource> acquire()
    {
        if (resources.empty())
        {
            std::cout << "No available resources. Creating a new one." << std::endl;
            return std::make_shared<Resource>();
        }
        else
        {
            std::shared_ptr<Resource> resource = resources.back();
            resources.pop_back();
            return resource;
        }
    }

    void release(std::shared_ptr<Resource> resource)
    {
        resources.push_back(resource);
    }

private:
    std::vector<std::shared_ptr<Resource>> resources;
};

int main()
{
    // Create an object pool with a size of 3
    ObjectPool pool(3);

    // Acquire and use resources
    auto resource1 = pool.acquire();
    resource1->operation();

    auto resource2 = pool.acquire();
    resource2->operation();

    // Release resources back to the pool
    pool.release(resource1);
    pool.release(resource2);

    // Acquire and use more resources
    auto resource3 = pool.acquire();
    resource3->operation();

    auto resource4 = pool.acquire();
    resource4->operation();

    return 0;
}
