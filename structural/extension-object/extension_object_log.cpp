#include <iostream>
#include <memory>
#include <string>

// Abstract interface for log extensions
class LogExtension
{
public:
    virtual void log(const std::string &message) = 0;
};

// Concrete implementation of a text log extension
class TextLogExtension : public LogExtension
{
public:
    void log(const std::string &message) override
    {
        std::cout << "Text Log: " << message << std::endl;
    }
};

// Concrete implementation of a JSON log extension
class JsonLogExtension : public LogExtension
{
public:
    void log(const std::string &message) override
    {
        std::cout << "JSON Log: {" << message << "}" << std::endl;
    }
};

// Logger class that uses extensions
class Logger
{
private:
    std::shared_ptr<LogExtension> extension;

public:
    void setExtension(std::shared_ptr<LogExtension> ext)
    {
        extension = ext;
    }

    void logMessage(const std::string &message)
    {
        if (extension)
        {
            extension->log(message);
        }
        else
        {
            std::cout << "Default Log: " << message << std::endl;
        }
    }
};

int main()
{
    Logger logger;

    // Use the default logger
    logger.logMessage("This is a default log message");

    // Add a TextLogExtension
    std::shared_ptr<LogExtension> textLogExt = std::make_shared<TextLogExtension>();
    logger.setExtension(textLogExt);
    logger.logMessage("This is a text log message");

    // Change to JSONLogExtension
    std::shared_ptr<LogExtension> jsonLogExt = std::make_shared<JsonLogExtension>();
    logger.setExtension(jsonLogExt);
    logger.logMessage("This is a JSON log message");

    return 0;
}
