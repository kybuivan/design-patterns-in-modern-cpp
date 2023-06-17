#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forward declarations
class EventListener
{
public:
    virtual ~EventListener() = default;

    virtual void handleEvent(const std::string &eventType, const std::string &eventData) = 0;
};

class EventManager
{
public:
    void addListener(std::shared_ptr<EventListener> listener)
    {
        m_listeners.push_back(listener);
    }

    void removeListener(std::shared_ptr<EventListener> listener)
    {
        m_listeners.erase(std::remove_if(m_listeners.begin(),
                                         m_listeners.end(),
                                         [&listener](const std::weak_ptr<EventListener> &wp) {
                                             return wp.expired() || wp.lock() == listener;
                                         }),
                          m_listeners.end());
    }

    void notify(const std::string &eventType, const std::string &eventData)
    {
        for (const auto &weakListener : m_listeners)
        {
            auto listener = weakListener.lock();
            if (listener)
            {
                listener->handleEvent(eventType, eventData);
            }
        }
    }

private:
    std::vector<std::weak_ptr<EventListener>> m_listeners;
};

class Editor
{
public:
    Editor(std::shared_ptr<EventManager> eventManager) : m_eventManager(eventManager)
    {
    }

    void openFile(const std::string &filePath)
    {
        // Open the file
        std::cout << "Opened file: " << filePath << std::endl;

        // Notify the event manager that a file was opened
        m_eventManager->notify("fileOpened", filePath);
    }

    void saveFile(const std::string &filePath)
    {
        // Save the file
        std::cout << "Saved file: " << filePath << std::endl;

        // Notify the event manager that a file was saved
        m_eventManager->notify("fileSaved", filePath);
    }

private:
    std::shared_ptr<EventManager> m_eventManager;
};

class EmailListener : public EventListener
{
public:
    virtual void handleEvent(const std::string &eventType, const std::string &eventData) override
    {
        if (eventType == "fileSaved")
        {
            std::cout << "Email sent: File '" << eventData << "' was saved." << std::endl;
        }
    }
};

class LoggingListener : public EventListener
{
public:
    virtual void handleEvent(const std::string &eventType, const std::string &eventData) override
    {
        std::cout << "Log entry created: " << eventType << " event with data '" << eventData << "'"
                  << std::endl;
    }
};

int main()
{
    // Create the event manager and the editor
    auto eventManager = std::make_shared<EventManager>();
    Editor editor(eventManager);

    // Create the event listeners
    auto emailListener = std::make_shared<EmailListener>();
    auto loggingListener = std::make_shared<LoggingListener>();

    // Add the event listeners to the event manager
    eventManager->addListener(emailListener);
    eventManager->addListener(loggingListener);

    // Open and save a file
    editor.openFile("myFile.txt");
    editor.saveFile("myFile.txt");

    // Remove the logging listener and save another file
    eventManager->removeListener(loggingListener);
    editor.saveFile("anotherFile.txt");

    return 0;
}
