#include <iostream>
#include <string>
#include <vector>

// Base class for Person
class Person
{
public:
    std::string name;
    std::string address;
    std::string job;

public:
    Person(const std::string &name, const std::string &address, const std::string &job)
        : name(name), address(address), job(job)
    {
    }

    void show()
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Address: " << address << std::endl;
        std::cout << "Job: " << job << std::endl;
    }
};

// Base class for Builder
class PersonBuilder
{
protected:
    Person person;

public:
    PersonBuilder(const std::string &name) : person{Person(name, "", "")}
    {
    }

    virtual ~PersonBuilder() = default;

    Person getPerson()
    {
        return person;
    }
};

// Derived class for address builder
class AddressBuilder : public PersonBuilder
{
public:
    AddressBuilder(const std::string &name) : PersonBuilder(name)
    {
    }

    AddressBuilder &at(const std::string &address)
    {
        person.address = address;
        return *this;
    }

    AddressBuilder &withPostcode(const std::string &postcode)
    {
        person.address = person.address + " " + postcode;
        return *this;
    }
};

// Derived class for job builder
class JobBuilder : public PersonBuilder
{
public:
    JobBuilder(const std::string &name) : PersonBuilder(name)
    {
    }

    JobBuilder &worksAsA(const std::string &job)
    {
        person.job = job;
        return *this;
    }
};

// Client
int main()
{
    Person person = PersonBuilder("John").getPerson();
    person.show();

    Person johnDoe =
        AddressBuilder("John Doe").at("123 Main St.").withPostcode("11111").getPerson();
    johnDoe.show();

    Person janeDoe = JobBuilder("Jane Doe").worksAsA("Engineer").getPerson();
    janeDoe.show();

    return 0;
}
