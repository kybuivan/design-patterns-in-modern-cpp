#include <iostream>
#include <string>

// Model (Weather Data)
class WeatherModel
{
private:
    std::string location;
    double temperature;
    double humidity;

public:
    WeatherModel(const std::string &loc, double temp, double hum) : location(loc), temperature(temp), humidity(hum)
    {
    }

    const std::string &getLocation() const
    {
        return location;
    }

    double getTemperature() const
    {
        return temperature;
    }

    double getHumidity() const
    {
        return humidity;
    }

    void updateWeather(double newTemp, double newHum)
    {
        temperature = newTemp;
        humidity = newHum;
    }
};

// View (Weather Display)
class WeatherView
{
public:
    void displayWeather(const WeatherModel &weather)
    {
        std::cout << "Location: " << weather.getLocation() << std::endl;
        std::cout << "Temperature: " << weather.getTemperature() << " °C" << std::endl;
        std::cout << "Humidity: " << weather.getHumidity() << "%" << std::endl;
    }
};

// Controller (Weather App)
class WeatherController
{
private:
    WeatherModel model;
    WeatherView view;

public:
    WeatherController(const std::string &location, double initialTemp, double initialHum) : model(location, initialTemp, initialHum)
    {
    }

    void updateWeatherData(double newTemp, double newHum)
    {
        model.updateWeather(newTemp, newHum);
        view.displayWeather(model);
    }
};

int main()
{
    WeatherController controller("City Name", 25.5, 60.0);

    controller.updateWeatherData(28.0, 55.5);
    controller.updateWeatherData(30.0, 50.0);

    return 0;
}
