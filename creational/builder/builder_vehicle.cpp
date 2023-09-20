#include <iostream>
#include <memory>
#include <string>

// Product: Vehicle
class Vehicle
{
public:
    void SetType(const std::string &type)
    {
        this->type = type;
    }

    void SetEngine(const std::string &engine)
    {
        this->engine = engine;
    }

    void SetWheels(int wheels)
    {
        this->wheels = wheels;
    }

    void SetSeats(int seats)
    {
        this->seats = seats;
    }

    void SetColor(const std::string &color)
    {
        this->color = color;
    }

    void DisplayInfo()
    {
        std::cout << "Vehicle Type: " << type << std::endl;
        std::cout << "Engine: " << engine << std::endl;
        std::cout << "Wheels: " << wheels << std::endl;
        std::cout << "Seats: " << seats << std::endl;
        std::cout << "Color: " << color << std::endl;
    }

private:
    std::string type;
    std::string engine;
    int wheels;
    int seats;
    std::string color;
};

// Abstract Builder: VehicleBuilder
class VehicleBuilder
{
public:
    virtual void BuildType() = 0;
    virtual void BuildEngine() = 0;
    virtual void BuildWheels() = 0;
    virtual void BuildSeats() = 0;
    virtual void BuildColor() = 0;
    virtual std::shared_ptr<Vehicle> GetVehicle() = 0;
};

// Concrete Builder: CarBuilder
class CarBuilder : public VehicleBuilder
{
public:
    CarBuilder()
    {
        vehicle = std::make_shared<Vehicle>();
    }

    void BuildType() override
    {
        vehicle->SetType("Car");
    }

    void BuildEngine() override
    {
        vehicle->SetEngine("V6");
    }

    void BuildWheels() override
    {
        vehicle->SetWheels(4);
    }

    void BuildSeats() override
    {
        vehicle->SetSeats(5);
    }

    void BuildColor() override
    {
        vehicle->SetColor("Red");
    }

    std::shared_ptr<Vehicle> GetVehicle() override
    {
        return vehicle;
    }

private:
    std::shared_ptr<Vehicle> vehicle;
};

// Concrete Builder: BicycleBuilder
class BicycleBuilder : public VehicleBuilder
{
public:
    BicycleBuilder()
    {
        vehicle = std::make_shared<Vehicle>();
    }

    void BuildType() override
    {
        vehicle->SetType("Bicycle");
    }

    void BuildEngine() override
    {
        vehicle->SetEngine("None");
    }

    void BuildWheels() override
    {
        vehicle->SetWheels(2);
    }

    void BuildSeats() override
    {
        vehicle->SetSeats(1);
    }

    void BuildColor() override
    {
        vehicle->SetColor("Black");
    }

    std::shared_ptr<Vehicle> GetVehicle() override
    {
        return vehicle;
    }

private:
    std::shared_ptr<Vehicle> vehicle;
};

// Director: VehicleManufacturer
class VehicleManufacturer
{
public:
    void SetBuilder(std::shared_ptr<VehicleBuilder> builder)
    {
        this->builder = builder;
    }

    std::shared_ptr<Vehicle> BuildVehicle()
    {
        builder->BuildType();
        builder->BuildEngine();
        builder->BuildWheels();
        builder->BuildSeats();
        builder->BuildColor();
        return builder->GetVehicle();
    }

private:
    std::shared_ptr<VehicleBuilder> builder;
};

int main()
{
    VehicleManufacturer manufacturer;

    // Build a car
    std::shared_ptr<VehicleBuilder> carBuilder = std::make_shared<CarBuilder>();
    manufacturer.SetBuilder(carBuilder);
    std::shared_ptr<Vehicle> car = manufacturer.BuildVehicle();

    // Build a bicycle
    std::shared_ptr<VehicleBuilder> bicycleBuilder = std::make_shared<BicycleBuilder>();
    manufacturer.SetBuilder(bicycleBuilder);
    std::shared_ptr<Vehicle> bicycle = manufacturer.BuildVehicle();

    // Display vehicle information
    car->DisplayInfo();
    std::cout << std::endl;
    bicycle->DisplayInfo();

    return 0;
}
