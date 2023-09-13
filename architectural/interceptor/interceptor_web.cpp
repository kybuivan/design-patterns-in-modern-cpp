#include <iostream>
#include <vector>

// Abstract Interceptor Class
class Interceptor
{
public:
    virtual void intercept() = 0;
};

// Concrete Interceptors
class LoggingInterceptor : public Interceptor
{
public:
    void intercept() override
    {
        std::cout << "Logging: Request received." << std::endl;
    }
};

class AuthenticationInterceptor : public Interceptor
{
public:
    void intercept() override
    {
        std::cout << "Authentication: User authenticated." << std::endl;
    }
};

class AuthorizationInterceptor : public Interceptor
{
public:
    void intercept() override
    {
        std::cout << "Authorization: User authorized." << std::endl;
    }
};

// Client (Handler)
class WebApplication
{
private:
    std::vector<Interceptor *> interceptors;

public:
    WebApplication()
    {
        // Configure the interceptor chain
        interceptors.push_back(new LoggingInterceptor());
        interceptors.push_back(new AuthenticationInterceptor());
        interceptors.push_back(new AuthorizationInterceptor());
    }

    void handleRequest()
    {
        // Execute the interceptor chain
        for (Interceptor *interceptor : interceptors)
        {
            interceptor->intercept();
        }
        // Core application logic goes here
        std::cout << "Handling the request." << std::endl;
    }
};

int main()
{
    WebApplication app;
    app.handleRequest();

    return 0;
}
