#include <iostream>
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
    virtual void printVehicleType() = 0;
};

class Car : public Vehicle
{
public:
    void printVehicleType()
    {
        std::cout << "Car" << std::endl;
    }
};

class Truck : public Vehicle
{
public:
    void printVehicleType()
    {
        std::cout << "Truck" << std::endl;
    }
};

class Bike : public Vehicle
{
public:
    void printVehicleType()
    {
        std::cout << "Bike" << std::endl;
    }
};

class VehicleFactory
{
public:
    static Vehicle* createVehicle(VehicleType type)
    {
        switch(type)
        {
            case VehicleType::CAR:
                return new Car;
            case VehicleType::TRUCK:
                return new Truck;
            case VehicleType::BIKE:
                return new Bike;
        }
        return nullptr;
    }
};

int main()
{
    VehicleType type = VehicleType::CAR;
    Vehicle* vehicle = VehicleFactory::createVehicle(type);
    vehicle->printVehicleType();
    return 0;
}
