#include <iostream>
#include <memory>
#include <string>

// Abstract Product: Address
class Address
{
public:
    virtual void SetStreet(const std::string &street) = 0;
    virtual void SetCity(const std::string &city) = 0;
    virtual void SetRegion(const std::string &region) = 0;
    virtual void SetPostalCode(const std::string &postalCode) = 0;
    virtual std::string GetFullAddress() const = 0;
};

// Concrete Product: USAddress
class USAddress : public Address
{
private:
    std::string street;
    std::string city;
    std::string region;
    std::string postalCode;

public:
    void SetStreet(const std::string &street) override
    {
        this->street = street;
    }

    void SetCity(const std::string &city) override
    {
        this->city = city;
    }

    void SetRegion(const std::string &region) override
    {
        this->region = region;
    }

    void SetPostalCode(const std::string &postalCode) override
    {
        this->postalCode = postalCode;
    }

    std::string GetFullAddress() const override
    {
        return street + ", " + city + ", " + region + ", " + postalCode;
    }
};

// Abstract Product: PhoneNumber
class PhoneNumber
{
public:
    virtual void SetNumber(const std::string &number) = 0;
    virtual std::string GetNumber() const = 0;
};

// Concrete Product: USPhoneNumber
class USPhoneNumber : public PhoneNumber
{
private:
    std::string number;

public:
    void SetNumber(const std::string &number) override
    {
        this->number = number;
    }

    std::string GetNumber() const override
    {
        return number;
    }
};

// Abstract Factory
class AbstractFactory
{
public:
    virtual std::shared_ptr<Address> CreateAddress() = 0;
    virtual std::shared_ptr<PhoneNumber> CreatePhoneNumber() = 0;
};

// Concrete Factory: USAddressFactory
class USAddressFactory : public AbstractFactory
{
public:
    std::shared_ptr<Address> CreateAddress() override
    {
        return std::make_shared<USAddress>();
    }

    std::shared_ptr<PhoneNumber> CreatePhoneNumber() override
    {
        return std::make_shared<USPhoneNumber>();
    }
};

int main()
{
    // Create a US address and phone number using the USAddressFactory
    std::shared_ptr<AbstractFactory> usFactory = std::make_shared<USAddressFactory>();

    std::shared_ptr<Address> usAddress = usFactory->CreateAddress();
    std::shared_ptr<PhoneNumber> usPhoneNumber = usFactory->CreatePhoneNumber();

    usAddress->SetStreet("123 Main St");
    usAddress->SetCity("New York");
    usAddress->SetRegion("NY");
    usAddress->SetPostalCode("10001");

    usPhoneNumber->SetNumber("+1 555-123-4567");

    // Display the created US address and phone number
    std::cout << "US Address: " << usAddress->GetFullAddress() << std::endl;
    std::cout << "US Phone Number: " << usPhoneNumber->GetNumber() << std::endl;

    return 0;
}
