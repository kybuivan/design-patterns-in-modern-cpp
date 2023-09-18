#include <iostream>
#include <memory>
#include <mutex>

class DatabaseConnection
{
private:
    std::string connectionString;
    std::shared_ptr<int> connection; // The actual database connection
    std::mutex mutex;                // Mutex for thread safety

public:
    DatabaseConnection(const std::string &connStr) : connectionString(connStr), connection(nullptr)
    {
    }

    // Function to establish the database connection, creating it if it doesn't exist yet
    std::shared_ptr<int> connect()
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (!connection)
        {
            // Simulate establishing a database connection
            // In a real application, this would involve connecting to a database server
            connection = std::make_shared<int>(42);
            std::cout << "Connected to database: " << connectionString << std::endl;
        }
        return connection;
    }

    // Function to disconnect from the database
    void disconnect()
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (connection)
        {
            // Simulate closing the database connection
            // In a real application, this would involve disconnecting from the database server
            connection.reset();
            std::cout << "Disconnected from database: " << connectionString << std::endl;
        }
    }
};

int main()
{
    // Create a database connection object
    DatabaseConnection dbConnection("my_database");

    // Access the database connection, which will create the connection
    std::shared_ptr<int> connection1 = dbConnection.connect();

    // Access the connection again, which won't create a new connection
    std::shared_ptr<int> connection2 = dbConnection.connect();

    // Disconnect from the database
    dbConnection.disconnect();

    // Access the connection again after disconnecting, which will create a new connection
    std::shared_ptr<int> connection3 = dbConnection.connect();

    return 0;
}
