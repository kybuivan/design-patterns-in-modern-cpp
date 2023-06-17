#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

class Address
{
public:
    std::string street, city, country;
    Address() = default;
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
    std::shared_ptr<Address> work_address;

public:
    Contact(const std::string &name, const std::shared_ptr<Address> &work_address)
        : name(name), work_address(work_address)
    {
    }
    friend std::ostream &operator<<(std::ostream &os, const Contact &obj)
    {
        return os << "name: " << obj.name << " work_address: " << *obj.work_address;
    }
};

class ContactPrototypeFactory
{
private:
    std::unordered_map<std::string, std::shared_ptr<Contact>> prototypes;

public:
    ContactPrototypeFactory()
    {
        prototypes["tom"] =
            std::make_shared<Contact>("tom",
                                      std::make_shared<Address>("123 London Road", "London", "UK"));
        prototypes["alice"] = std::make_shared<Contact>(
            "alice",
            std::make_shared<Address>("456 Paris Road", "Paris", "France"));
    }
    std::shared_ptr<Contact> create_contact(const std::string &name)
    {
        auto it = prototypes.find(name);
        if (it == prototypes.end())
        {
            std::stringstream ss;
            ss << "Prototype with name " << name << " not found";
            throw std::invalid_argument(ss.str());
        }
        return std::make_shared<Contact>(*it->second);
    }
};

int main()
{
    ContactPrototypeFactory factory;
    auto john = factory.create_contact("tom");
    auto jane = factory.create_contact("alice");

    std::cout << *john << std::endl;
    std::cout << *jane << std::endl;

    return 0;
}
