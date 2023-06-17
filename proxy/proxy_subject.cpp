#include <iostream>
#include <string>

class Subject
{
public:
    virtual ~Subject() = default;
    virtual void request() = 0;
};

class RealSubject : public Subject
{
public:
    void request() override
    {
        std::cout << "Request handled by the RealSubject" << std::endl;
    }
};

class Proxy : public Subject
{
private:
    RealSubject *realSubject;

public:
    Proxy()
    {
        realSubject = new RealSubject();
    }

    void request() override
    {
        std::cout << "Request handled by the Proxy" << std::endl;
        realSubject->request();
    }
};

int main()
{
    Subject *subject = new Proxy();
    subject->request();
    return 0;
}
