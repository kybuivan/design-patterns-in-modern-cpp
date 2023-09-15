#include <functional>
#include <iostream>
#include <vector>

class TemperatureSensor
{
public:
    TemperatureSensor(const std::string &name, int initial_temperature) : name_(name), temperature_(initial_temperature)
    {
    }

    int getTemperature() const
    {
        return temperature_;
    }

    void setTemperature(int new_temperature)
    {
        temperature_ = new_temperature;
        std::cout << name_ << " temperature updated to " << temperature_ << "°C." << std::endl;
    }

    void updateTargetTemperature(int new_target)
    {
        std::cout << name_ << " adjusting to new target temperature: " << new_target << "°C." << std::endl;
        setTemperature(new_target); // Adjust temperature to the new target
    }

private:
    std::string name_;
    int temperature_;
};

class Thermostat
{
public:
    Thermostat(int target) : target_temperature_(target)
    {
    }

    int getTargetTemperature() const
    {
        return target_temperature_;
    }

    void setTargetTemperature(int new_target)
    {
        target_temperature_ = new_target;
        notify(); // Notify sensors of the new target temperature
    }

    void bindSensor(TemperatureSensor &sensor)
    {
        bound_sensors_.push_back(&sensor);
    }

    void notify()
    {
        for (auto &sensor : bound_sensors_)
        {
            sensor->updateTargetTemperature(target_temperature_);
        }
    }

private:
    int target_temperature_;
    std::vector<TemperatureSensor *> bound_sensors_;
};

int main()
{
    Thermostat thermostat(22); // Initial target temperature

    TemperatureSensor sensor1("Living Room", 20);
    TemperatureSensor sensor2("Bedroom", 25);

    // Bind the sensors to the thermostat
    thermostat.bindSensor(sensor1);
    thermostat.bindSensor(sensor2);

    std::cout << "Thermostat target temperature: " << thermostat.getTargetTemperature() << "°C" << std::endl;

    // Change the target temperature on the thermostat
    thermostat.setTargetTemperature(23);

    return 0;
}
