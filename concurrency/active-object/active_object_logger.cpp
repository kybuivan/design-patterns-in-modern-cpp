#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class Logger
{
public:
    Logger() : isRunning(true)
    {
        workerThread = std::thread(&Logger::processMessages, this);
    }

    ~Logger()
    {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            isRunning = false;
        }
        condition.notify_one();
        workerThread.join();
    }

    void log(const std::string &message)
    {
        auto logTask = [message]() { std::cout << "Log: " << message << std::endl; };

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            logQueue.push(logTask);
        }

        condition.notify_one();
    }

private:
    std::thread workerThread;
    std::queue<std::function<void()>> logQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool isRunning;

    void processMessages()
    {
        while (true)
        {
            std::function<void()> logTask;

            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return !logQueue.empty() || !isRunning; });

                if (!isRunning && logQueue.empty())
                {
                    break; // Exit the thread if not running and queue is empty
                }

                logTask = logQueue.front();
                logQueue.pop();
            }

            logTask(); // Execute the log task
        }
    }
};

int main()
{
    Logger logger;

    // Enqueue log messages
    logger.log("Message 1");
    logger.log("Message 2");
    logger.log("Message 3");

    // Sleep to allow time for log processing
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // More log messages
    logger.log("Message 4");
    logger.log("Message 5");

    return 0;
}
