#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:
    ThreadPool(size_t numThreads) : isShuttingDown(false)
    {
        for (size_t i = 0; i < numThreads; ++i)
        {
            threads.emplace_back([this] { workerThread(); });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            isShuttingDown = true;
        }
        condition.notify_all();

        for (std::thread &thread : threads)
        {
            thread.join();
        }
    }

    void submitTask(std::function<void()> task)
    {
        if (isShuttingDown)
        {
            std::cout << "ThreadPool is shutting down. Task submission is balking." << std::endl;
            return; // Balk if shutting down
        }

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            taskQueue.push(task);
        }
        condition.notify_one();
    }

private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool isShuttingDown;

    void workerThread()
    {
        while (true)
        {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return !taskQueue.empty() || isShuttingDown; });

                if (isShuttingDown && taskQueue.empty())
                {
                    break; // Exit the thread if shutting down and no tasks left
                }

                task = taskQueue.front();
                taskQueue.pop();
            }

            task(); // Execute the task
        }
    }
};

int main()
{
    ThreadPool threadPool(2);

    // Submit tasks to the thread pool
    threadPool.submitTask([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Task 1 completed." << std::endl;
    });

    threadPool.submitTask([]() { std::cout << "Task 2 completed." << std::endl; });

    // Shut down the thread pool
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Shutting down the thread pool." << std::endl;

    return 0;
}
