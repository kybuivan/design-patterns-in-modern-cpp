#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// Reusable Object: Database Connection
class DatabaseConnection
{
public:
    DatabaseConnection(const std::string &dbName) : dbName(dbName)
    {
        std::cout << "Establishing a database connection to " << dbName << std::endl;
    }

    void executeQuery(const std::string &query)
    {
        std::cout << "Executing query '" << query << "' on database " << dbName << std::endl;
        // Simulate database query execution
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void close()
    {
        std::cout << "Closing the database connection to " << dbName << std::endl;
    }

private:
    std::string dbName;
};

// Object Pool
class ConnectionPool
{
public:
    ConnectionPool(const std::string &dbName, int poolSize) : dbName(dbName), poolSize(poolSize)
    {
        for (int i = 0; i < poolSize; ++i)
        {
            connections.push_back(std::make_shared<DatabaseConnection>(dbName));
        }
    }

    std::shared_ptr<DatabaseConnection> acquire()
    {
        std::unique_lock<std::mutex> lock(mutex);
        if (connections.empty())
        {
            std::cout << "No available connections. Waiting..." << std::endl;
            condition.wait(lock, [this] { return !connections.empty(); });
        }
        std::shared_ptr<DatabaseConnection> connection = connections.back();
        connections.pop_back();
        return connection;
    }

    void release(std::shared_ptr<DatabaseConnection> connection)
    {
        std::unique_lock<std::mutex> lock(mutex);
        connections.push_back(connection);
        lock.unlock();
        condition.notify_one(); // Notify waiting threads that a connection is available
    }

private:
    std::string dbName;
    int poolSize;
    std::vector<std::shared_ptr<DatabaseConnection>> connections;
    std::mutex mutex;
    std::condition_variable condition;
};

// Function to simulate database queries
void executeDatabaseQuery(ConnectionPool &pool, int queryNumber)
{
    auto connection = pool.acquire();
    connection->executeQuery("Query " + std::to_string(queryNumber));
    pool.release(connection);
}

int main()
{
    // Create a connection pool with a size of 3 for a database named "MyDatabase"
    ConnectionPool pool("MyDatabase", 3);

    // Simulate multiple threads executing database queries
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.emplace_back(executeDatabaseQuery, std::ref(pool), i);
    }

    // Join all threads
    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}
