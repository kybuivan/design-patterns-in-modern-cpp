#include <iostream>
#include <mutex>

class Heater
{
public:
    Heater(int threshold) : threshold(threshold), isOn(false)
    {
    }

    void turnOn(int roomTemperature)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (roomTemperature < threshold && !isOn)
        {
            std::cout << "Heater is turned on." << std::endl;
            isOn = true;
        }
        else
        {
            std::cout << "Heater balks. Room temperature is too high or heater is already on." << std::endl;
        }
    }

    void turnOff()
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (isOn)
        {
            std::cout << "Heater is turned off." << std::endl;
            isOn = false;
        }
    }

private:
    int threshold;
    bool isOn;
    std::mutex mutex;
};

int main()
{
    Heater heater(70); // Set the temperature threshold to 70 degrees

    // Simulate room temperature changes
    int roomTemperature1 = 65;
    int roomTemperature2 = 75;

    heater.turnOn(roomTemperature1); // Turn on the heater when it's too cold
    heater.turnOn(roomTemperature2); // Balk because the room is already warm
    heater.turnOff();                // Turn off the heater

    return 0;
}
