#include <iostream>
#include <map>
#include <memory>
#include <string>

class Object
{
public:
    virtual void print() = 0;
};

class ConcreteObjectA : public Object
{
public:
    void print()
    {
        std::cout << "I am a Concrete Object A" << std::endl;
    }
};

class ConcreteObjectB : public Object
{
public:
    void print()
    {
        std::cout << "I am a Concrete Object B" << std::endl;
    }
};

class ObjectFactory
{
public:
    static std::shared_ptr<Object> createObject(const std::string &type)
    {
        if (type == "A")
        {
            return std::make_shared<ConcreteObjectA>();
        }
        else if (type == "B")
        {
            return std::make_shared<ConcreteObjectB>();
        }
        else
        {
            return nullptr;
        }
    }
};

class ObjectTracker
{
private:
    static std::map<std::string, int> objectCounter;

public:
    static void trackObject(const std::string &type)
    {
        if (objectCounter.count(type) == 0)
        {
            objectCounter[type] = 1;
        }
        else
        {
            objectCounter[type]++;
        }
    }

    static void printCount()
    {
        for (auto &item : objectCounter)
        {
            std::cout << "Type " << item.first << ": " << item.second << " objects created."
                      << std::endl;
        }
    }
};

std::map<std::string, int> ObjectTracker::objectCounter;

int main()
{
    auto objectA = ObjectFactory::createObject("A");
    auto objectB = ObjectFactory::createObject("B");
    auto objectC = ObjectFactory::createObject("C");

    ObjectTracker::trackObject("A");
    ObjectTracker::trackObject("B");
    ObjectTracker::trackObject("C");

    ObjectTracker::printCount();

    return 0;
}
