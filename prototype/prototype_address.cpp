#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Address
{
public:
    std::string street, city, country;
    Address()
    {
    }
    Address(const std::string &street, const std::string &city, const std::string &country)
        : street(street), city(city), country(country)
    {
    }
    friend std::ostream &operator<<(std::ostream &os, const Address &obj)
    {
        return os << "street: " << obj.street << " city: " << obj.city
                  << " country: " << obj.country;
    }
};

class Contact
{
private:
    std::string name;
    Address *work_address;

public:
    Contact(const std::string &name, Address *const work_address)
        : name(name), work_address(new Address(*work_address))
    {
    }
    ~Contact()
    {
        delete work_address;
    }
    Contact(const Contact &other) : name(other.name), work_address(new Address(*other.work_address))
    {
    }
    Contact &operator=(const Contact &other)
    {
        if (this != &other)
        {
            delete work_address;
            name = other.name;
            work_address = new Address(*other.work_address);
        }
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &os, const Contact &obj)
    {
        return os << "name: " << obj.name << " work_address: " << *obj.work_address;
    }
};

class ContactPrototypeFactory
{
private:
    std::unordered_map<std::string, Contact *> prototypes;

public:
    ContactPrototypeFactory()
    {
        prototypes["tom"] = new Contact("tom", new Address("123 London Road", "London", "UK"));
        prototypes["alice"] =
            new Contact("alice", new Address("456 Paris Road", "Paris", "France"));
    }
    ~ContactPrototypeFactory()
    {
        for (const auto &pair : prototypes)
        {
            delete pair.second;
        }
    }
    Contact *create_contact(const std::string &name)
    {
        auto it = prototypes.find(name);
        if (it == prototypes.end())
        {
            std::stringstream ss;
            ss << "Prototype with name " << name << " not found";
            throw std::invalid_argument(ss.str());
        }
        return new Contact(*it->second);
    }
};

int main()
{
    ContactPrototypeFactory factory;
    auto john = factory.create_contact("tom");
    auto jane = factory.create_contact("alice");

    std::cout << *john << std::endl;
    std::cout << *jane << std::endl;

    delete john;
    delete jane;

    return 0;
}
