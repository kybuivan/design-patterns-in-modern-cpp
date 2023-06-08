#include <iostream>
#include <string>

template <typename T>
class Singleton
{
private:
    static T *instance;

protected:
    Singleton()
    {
    }

public:
    static T *getInstance()
    {
        if (!instance)
        {
            instance = new T();
        }

        return instance;
    }
};

template <typename T>
T *Singleton<T>::instance = nullptr;

class Config : public Singleton<Config>
{
private:
    int port;
    std::string host;

public:
    int getPort() const
    {
        return port;
    }
    void setPort(int p)
    {
        port = p;
    }

    std::string getHost() const
    {
        return host;
    }
    void setHost(const std::string &h)
    {
        host = h;
    }
};

class Logger : public Singleton<Logger>
{
public:
    void log(const std::string &msg)
    {
        std::cout << "Log: " << msg << std::endl;
    }
};

int main()
{
    Config *config = Config::getInstance();
    config->setHost("localhost");
    config->setPort(8080);

    Logger *logger = Logger::getInstance();
    logger->log("Application started");

    return 0;
}
