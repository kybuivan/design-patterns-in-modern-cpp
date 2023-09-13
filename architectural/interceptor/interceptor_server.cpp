#include <iostream>
#include <memory>
#include <vector>

// Abstract Interceptor Interface
class Interceptor
{
public:
    virtual void intercept(std::string &request, std::string &response) = 0;
};

// Concrete Interceptors
class AuthenticationInterceptor : public Interceptor
{
public:
    void intercept(std::string &request, std::string &response) override
    {
        // Simulate user authentication
        std::cout << "Authentication: User authenticated." << std::endl;
    }
};

class LoggingInterceptor : public Interceptor
{
public:
    void intercept(std::string &request, std::string &response) override
    {
        // Simulate request logging
        std::cout << "Logging: Request received." << std::endl;
    }
};

class AuthorizationInterceptor : public Interceptor
{
public:
    void intercept(std::string &request, std::string &response) override
    {
        // Simulate user authorization
        std::cout << "Authorization: User authorized." << std::endl;
    }
};

class ResponseModificationInterceptor : public Interceptor
{
public:
    void intercept(std::string &request, std::string &response) override
    {
        // Simulate response modification
        response += "\nModified by ResponseModificationInterceptor.";
        std::cout << "Response Modification: Response modified." << std::endl;
    }
};

// Client (Web Server)
class WebServer
{
private:
    std::vector<std::shared_ptr<Interceptor>> interceptors;

public:
    WebServer()
    {
        // Configure interceptors
        interceptors.push_back(std::make_shared<AuthenticationInterceptor>());
        interceptors.push_back(std::make_shared<LoggingInterceptor>());
        interceptors.push_back(std::make_shared<AuthorizationInterceptor>());
        interceptors.push_back(std::make_shared<ResponseModificationInterceptor>());
    }

    void handleRequest(std::string &request, std::string &response)
    {
        // Execute request interceptors
        for (const auto &interceptor : interceptors)
        {
            interceptor->intercept(request, response);
        }

        // Process the request and generate a response
        response += "\nResponse from the web server.";

        // Execute response interceptors
        for (const auto &interceptor : interceptors)
        {
            interceptor->intercept(request, response);
        }
    }
};

int main()
{
    WebServer server;

    std::string request = "HTTP GET /example";
    std::string response;

    // Simulate handling an HTTP request
    server.handleRequest(request, response);

    // Print the final response
    std::cout << "Final Response: " << response << std::endl;

    return 0;
}
