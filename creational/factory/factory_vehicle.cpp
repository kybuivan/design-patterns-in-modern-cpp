#include <iostream>
#include <memory>
#include <string>

enum class VehicleType
{
    CAR,
    TRUCK,
    BIKE
};

class Vehicle
{
public:
    virtual ~Vehicle() = default;
    virtual void printVehicleType() = 0;
};

class Car : public Vehicle
{
public:
    void printVehicleType() override
    {
        std::cout << "Car" << std::endl;
    }
};

class Truck : public Vehicle
{
public:
    void printVehicleType() override
    {
        std::cout << "Truck" << std::endl;
    }
};

class Bike : public Vehicle
{
public:
    void printVehicleType() override
    {
        std::cout << "Bike" << std::endl;
    }
};

class VehicleFactory
{
public:
    static std::unique_ptr<Vehicle> createVehicle(VehicleType type)
    {
        switch (type)
        {
        case VehicleType::CAR:
            return std::make_unique<Car>();
        case VehicleType::TRUCK:
            return std::make_unique<Truck>();
        case VehicleType::BIKE:
            return std::make_unique<Bike>();
        }
        return nullptr;
    }
};

int main()
{
    VehicleType type = VehicleType::CAR;
    std::unique_ptr<Vehicle> vehicle = VehicleFactory::createVehicle(type);
    vehicle->printVehicleType();

    return 0;
}
