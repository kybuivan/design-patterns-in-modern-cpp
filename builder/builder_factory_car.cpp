#include <iostream>
#include <memory>
#include <string>

// Base class for Vehicle
class Vehicle
{
public:
    std::string type;
    std::string wheels;
    std::string seats;

public:
    Vehicle(const std::string &type, const std::string &wheels, const std::string &seats)
        : type(type), wheels(wheels), seats(seats)
    {
    }

    virtual void show()
    {
        std::cout << "Type: " << type << std::endl;
        std::cout << "Wheels: " << wheels << std::endl;
        std::cout << "Seats: " << seats << std::endl;
    }
};

// Base class for VehicleBuilder
class VehicleBuilder
{
protected:
    Vehicle vehicle;

public:
    VehicleBuilder() : vehicle("", "", "")
    {
    }

    virtual ~VehicleBuilder() = default;

    Vehicle getVehicle()
    {
        return vehicle;
    }
};

// Derived class for CarBuilder
class CarBuilder : public VehicleBuilder
{
public:
    CarBuilder()
    {
        vehicle.type = "Car";
        vehicle.wheels = "4";
        vehicle.seats = "5";
    }
};

// Derived class for TruckBuilder
class TruckBuilder : public VehicleBuilder
{
public:
    TruckBuilder()
    {
        vehicle.type = "Truck";
        vehicle.wheels = "6";
        vehicle.seats = "3";
    }
};

// Factory class for creating Vehicles
class VehicleFactory
{
public:
    static std::unique_ptr<VehicleBuilder> createVehicle(const std::string &type)
    {
        if (type == "Car")
            return std::make_unique<CarBuilder>();
        else if (type == "Truck")
            return std::make_unique<TruckBuilder>();

        return nullptr;
    }
};

// Client
int main()
{
    std::unique_ptr<VehicleBuilder> carBuilder = VehicleFactory::createVehicle("Car");
    Vehicle car = carBuilder->getVehicle();
    car.show();

    std::unique_ptr<VehicleBuilder> truckBuilder = VehicleFactory::createVehicle("Truck");
    Vehicle truck = truckBuilder->getVehicle();
    truck.show();

    return 0;
}
