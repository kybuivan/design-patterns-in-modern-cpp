#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// Abstract base class for SaveGameService
class SaveGameService
{
public:
    virtual void saveProgress(const std::string &playerName, int level) = 0;
    virtual int loadProgress(const std::string &playerName) = 0;
};

// Concrete service: LocalSaveGameService
class LocalSaveGameService : public SaveGameService
{
public:
    void saveProgress(const std::string &playerName, int level) override
    {
        // Simulate saving progress locally
        std::cout << "LocalSaveGameService: Saving " << playerName << "'s progress to local storage. Level: " << level
                  << std::endl;
    }

    int loadProgress(const std::string &playerName) override
    {
        // Simulate loading progress from local storage
        std::cout << "LocalSaveGameService: Loading " << playerName << "'s progress from local storage." << std::endl;
        // In a real game, you would return the actual saved progress.
        return 0;
    }
};

// Concrete service: CloudSaveGameService
class CloudSaveGameService : public SaveGameService
{
public:
    void saveProgress(const std::string &playerName, int level) override
    {
        // Simulate saving progress to a cloud service
        std::cout << "CloudSaveGameService: Saving " << playerName << "'s progress to the cloud. Level: " << level
                  << std::endl;
    }

    int loadProgress(const std::string &playerName) override
    {
        // Simulate loading progress from the cloud
        std::cout << "CloudSaveGameService: Loading " << playerName << "'s progress from the cloud." << std::endl;
        // In a real game, you would return the actual saved progress.
        return 0;
    }
};

// Service Locator class
class ServiceLocator
{
public:
    // Register a service with the locator
    static void registerService(const std::string &serviceName, std::shared_ptr<SaveGameService> service)
    {
        services[serviceName] = service;
    }

    // Get a service by name
    static std::shared_ptr<SaveGameService> getService(const std::string &serviceName)
    {
        auto it = services.find(serviceName);
        if (it != services.end())
        {
            return it->second;
        }
        return nullptr; // Service not found
    }

private:
    static std::unordered_map<std::string, std::shared_ptr<SaveGameService>> services;
};

// Initialize the services
std::unordered_map<std::string, std::shared_ptr<SaveGameService>> ServiceLocator::services;

// Game class that uses services to save and load progress
class Game
{
public:
    void play(const std::string &playerName)
    {
        // Use services from the Service Locator
        auto saveGameService = ServiceLocator::getService("SaveGameService");

        if (saveGameService)
        {
            // Simulate gameplay and level progression
            int currentLevel = saveGameService->loadProgress(playerName);
            std::cout << "Player " << playerName << " is starting from level " << currentLevel << std::endl;
            currentLevel++; // Simulate advancing to the next level
            saveGameService->saveProgress(playerName, currentLevel);
            std::cout << "Player " << playerName << " has reached level " << currentLevel << std::endl;
        }
    }
};

int main()
{
    // Register services with the Service Locator
    ServiceLocator::registerService("SaveGameService", std::make_shared<CloudSaveGameService>());

    // Create and play the game
    Game game;
    game.play("Player1");

    return 0;
}
