#include <iostream>
#include <vector>
#include <string>

// Forward declarations
class EventListener {
public:
    virtual void handleEvent(const std::string& eventType, const std::string& eventData) = 0;
};

class EventManager {
public:
    void addListener(EventListener* listener) {
        m_listeners.push_back(listener);
    }

    void removeListener(EventListener* listener) {
        auto it = std::find(m_listeners.begin(), m_listeners.end(), listener);
        if (it != m_listeners.end()) {
            m_listeners.erase(it);
        }
    }

    void notify(const std::string& eventType, const std::string& eventData) {
        for (auto listener : m_listeners) {
            listener->handleEvent(eventType, eventData);
        }
    }

private:
    std::vector<EventListener*> m_listeners;
};

class Editor {
public:
    Editor(EventManager* eventManager) : m_eventManager(eventManager) {}

    void openFile(const std::string& filePath) {
        // Open the file
        std::cout << "Opened file: " << filePath << std::endl;

        // Notify the event manager that a file was opened
        m_eventManager->notify("fileOpened", filePath);
    }

    void saveFile(const std::string& filePath) {
        // Save the file
        std::cout << "Saved file: " << filePath << std::endl;

        // Notify the event manager that a file was saved
        m_eventManager->notify("fileSaved", filePath);
    }

private:
    EventManager* m_eventManager;
};

class EmailListener : public EventListener {
public:
    virtual void handleEvent(const std::string& eventType, const std::string& eventData) override {
        if (eventType == "fileSaved") {
            std::cout << "Email sent: File '" << eventData << "' was saved." << std::endl;
        }
    }
};

class LoggingListener : public EventListener {
public:
    virtual void handleEvent(const std::string& eventType, const std::string& eventData) override {
        std::cout << "Log entry created: " << eventType << " event with data '" << eventData << "'" << std::endl;
    }
};

int main() {
    // Create the event manager and the editor
    EventManager eventManager;
    Editor editor(&eventManager);

    // Create the event listeners
    EmailListener emailListener;
    LoggingListener loggingListener;

    // Add the event listeners to the event manager
    eventManager.addListener(&emailListener);
    eventManager.addListener(&loggingListener);

    // Open and save a file
    editor.openFile("myFile.txt");
    editor.saveFile("myFile.txt");

    // Remove the logging listener and save another file
    eventManager.removeListener(&loggingListener);
    editor.saveFile("anotherFile.txt");

    return 0;
}
