#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

class DatabaseConnection
{
private:
    std::string connectionString;

public:
    DatabaseConnection(const std::string &connStr) : connectionString(connStr)
    {
    }

    void connect()
    {
        // Simulate connecting to a database with the given connection string
        std::cout << "Connected to database: " << connectionString << std::endl;
    }

    void disconnect()
    {
        // Simulate disconnecting from the database
        std::cout << "Disconnected from database: " << connectionString << std::endl;
    }
};

class DatabaseMultiton
{
private:
    static std::unordered_map<std::string, std::shared_ptr<DatabaseConnection>> instances;

public:
    static std::shared_ptr<DatabaseConnection> getInstance(const std::string &key)
    {
        if (instances.find(key) == instances.end())
        {
            // Create a new instance and store it in the map
            instances[key] = std::make_shared<DatabaseConnection>(key);
            instances[key]->connect();
        }
        return instances[key];
    }

    static void releaseInstance(const std::string &key)
    {
        if (instances.find(key) != instances.end())
        {
            // Disconnect and remove the instance from the map
            instances[key]->disconnect();
            instances.erase(key);
        }
    }
};

std::unordered_map<std::string, std::shared_ptr<DatabaseConnection>> DatabaseMultiton::instances;

int main()
{
    // Get or create database connections by keys
    std::shared_ptr<DatabaseConnection> db1 = DatabaseMultiton::getInstance("Database1");
    std::shared_ptr<DatabaseConnection> db2 = DatabaseMultiton::getInstance("Database2");

    // Use the connections
    // ...

    // Release the connections when they are no longer needed
    DatabaseMultiton::releaseInstance("Database1");
    DatabaseMultiton::releaseInstance("Database2");

    return 0;
}
