#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// Abstract base class for services
class Service
{
public:
    virtual void execute() = 0;
};

// Concrete service: AudioService
class AudioService : public Service
{
public:
    void execute() override
    {
        std::cout << "AudioService is playing background music." << std::endl;
    }
};

// Concrete service: InputService
class InputService : public Service
{
public:
    void execute() override
    {
        std::cout << "InputService is handling player input." << std::endl;
    }
};

// Concrete service: PhysicsService
class PhysicsService : public Service
{
public:
    void execute() override
    {
        std::cout << "PhysicsService is simulating game physics." << std::endl;
    }
};

// Service Locator class
class ServiceLocator
{
public:
    // Register a service with the locator
    static void registerService(const std::string &serviceName, std::shared_ptr<Service> service)
    {
        services[serviceName] = service;
    }

    // Get a service by name
    static std::shared_ptr<Service> getService(const std::string &serviceName)
    {
        auto it = services.find(serviceName);
        if (it != services.end())
        {
            return it->second;
        }
        return nullptr; // Service not found
    }

private:
    static std::unordered_map<std::string, std::shared_ptr<Service>> services;
};

// Initialize the services
std::unordered_map<std::string, std::shared_ptr<Service>> ServiceLocator::services;

// Game class that uses services
class Game
{
public:
    void start()
    {
        // Use services from the Service Locator
        auto audioService = ServiceLocator::getService("AudioService");
        auto inputService = ServiceLocator::getService("InputService");
        auto physicsService = ServiceLocator::getService("PhysicsService");

        if (audioService)
        {
            audioService->execute();
        }

        if (inputService)
        {
            inputService->execute();
        }

        if (physicsService)
        {
            physicsService->execute();
        }
    }
};

int main()
{
    // Register services with the Service Locator
    ServiceLocator::registerService("AudioService", std::make_shared<AudioService>());
    ServiceLocator::registerService("InputService", std::make_shared<InputService>());
    ServiceLocator::registerService("PhysicsService", std::make_shared<PhysicsService>());

    // Create and start the game
    Game game;
    game.start();

    return 0;
}
