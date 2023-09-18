#include <iostream>
#include <stdexcept>
#include <string>

// Simulated network library
class NetworkLibrary
{
public:
    static void connect(const std::string &address)
    {
        std::cout << "Connected to: " << address << std::endl;
    }

    static void disconnect(const std::string &address)
    {
        std::cout << "Disconnected from: " << address << std::endl;
    }
};

class NetworkConnection
{
private:
    std::string serverAddress;

public:
    NetworkConnection(const std::string &address) : serverAddress(address)
    {
        NetworkLibrary::connect(serverAddress);
    }

    ~NetworkConnection()
    {
        NetworkLibrary::disconnect(serverAddress);
    }

    void sendData(const std::string &data)
    {
        std::cout << "Sending data to " << serverAddress << ": " << data << std::endl;
        // Simulate sending data over the network
    }
};

int main()
{
    try
    {
        NetworkConnection connection("example.com");

        // Use the network connection
        connection.sendData("Hello, Server!");

        // The network connection will be automatically closed when 'connection' goes out of scope
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 'connection' has gone out of scope, and the destructor has closed the network connection
    return 0;
}
