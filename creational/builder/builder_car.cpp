#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Product
class Car
{
public:
    std::string make;
    std::string model;
    int year;
    std::vector<std::string> options;

public:
    Car(const std::string &make,
        const std::string &model,
        int year,
        const std::vector<std::string> &options)
        : make(make), model(model), year(year), options(options)
    {
    }

    void show()
    {
        std::cout << "Make: " << make << std::endl;
        std::cout << "Model: " << model << std::endl;
        std::cout << "Year: " << year << std::endl;
        std::cout << "Options: ";
        for (const auto &option : options)
        {
            std::cout << option << " ";
        }
        std::cout << std::endl;
    }
};

// Abstract Builder
class CarBuilder
{
public:
    virtual ~CarBuilder() = default;
    virtual void setMake() = 0;
    virtual void setModel() = 0;
    virtual void setYear() = 0;
    virtual void addOption(const std::string &option) = 0;
    virtual std::unique_ptr<Car> build() = 0;
};

// Concrete Builder
class HondaBuilder : public CarBuilder
{
private:
    std::unique_ptr<Car> car;

public:
    HondaBuilder() : car{std::make_unique<Car>("Honda", "", 0, std::vector<std::string>())}
    {
    }

    void setMake() override
    {
        car->make = "Honda";
    }

    void setModel() override
    {
        car->model = "Civic";
    }

    void setYear() override
    {
        car->year = 2022;
    }

    void addOption(const std::string &option) override
    {
        car->options.push_back(option);
    }

    std::unique_ptr<Car> build() override
    {
        return std::move(car);
    }
};

// Director
class CarDirector
{
private:
    CarBuilder &builder;

public:
    CarDirector(CarBuilder &builder) : builder(builder)
    {
    }

    void buildCar()
    {
        builder.setMake();
        builder.setModel();
        builder.setYear();
        builder.addOption("Sunroof");
        builder.addOption("Leather Seats");
    }
};

// Client
int main()
{
    HondaBuilder hondaBuilder;
    CarDirector carDirector(hondaBuilder);
    carDirector.buildCar();
    std::unique_ptr<Car> car = hondaBuilder.build();
    car->show();

    return 0;
}
