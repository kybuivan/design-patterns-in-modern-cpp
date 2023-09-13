#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class ActiveObject
{
public:
    ActiveObject() : isRunning(true)
    {
        workerThread = std::thread(&ActiveObject::run, this);
    }

    ~ActiveObject()
    {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            isRunning = false;
        }
        condition.notify_one();
        workerThread.join();
    }

    template <typename Func>
    std::future<typename std::result_of<Func()>::type> enqueue(Func func)
    {
        using ReturnType = typename std::result_of<Func()>::type;

        auto promise = std::make_shared<std::promise<ReturnType>>();
        auto future = promise->get_future();

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            methodQueue.push([func, promise]() { promise->set_value(func()); });
        }

        condition.notify_one();
        return future;
    }

private:
    std::thread workerThread;
    std::queue<std::function<void()>> methodQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool isRunning;

    void run()
    {
        while (true)
        {
            std::function<void()> method;

            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return !methodQueue.empty() || !isRunning; });

                if ((!isRunning && methodQueue.empty()))
                {
                    break;
                }

                method = methodQueue.front();
                methodQueue.pop();
            }

            method();
        }
    }
};

int main()
{
    ActiveObject activeObject;

    auto future1 = activeObject.enqueue([]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return "Task 1 completed.";
    });

    auto future2 = activeObject.enqueue([]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return "Task 2 completed.";
    });

    std::cout << future1.get() << std::endl;
    std::cout << future2.get() << std::endl;

    return 0;
}
