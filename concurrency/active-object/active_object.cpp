#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ActiveObject
{
public:
    ActiveObject() : stop(false)
    {
        workerThread = std::thread([this] { this->run(); });
    }

    ~ActiveObject()
    {
        stop = true;
        workerThread.join();
    }

    template <typename Func>
    auto enqueue(Func func) -> std::future<typename std::invoke_result<Func>::type>
    {
        using ReturnType = typename std::invoke_result<Func>::type;
        auto task = std::make_shared<std::packaged_task<ReturnType()>>(func);
        auto future = task->get_future();

        {
            std::lock_guard<std::mutex> lock(mutex);
            tasks.push([task]() { (*task)(); });
        }

        condition.notify_one();
        return future;
    }

private:
    void run()
    {
        while (!stop)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex);
                condition.wait(lock, [this] { return stop || !tasks.empty(); });
                if (!tasks.empty())
                {
                    task = std::move(tasks.front());
                    tasks.pop();
                }
            }
            if (task)
            {
                task();
            }
        }
    }

    std::thread workerThread;
    std::mutex mutex;
    std::condition_variable condition;
    std::queue<std::function<void()>> tasks;
    bool stop;
};

int main()
{
    ActiveObject activeObject;

    auto future1 = activeObject.enqueue([]() {
        std::cout << "Task 1 executed." << std::endl;
        return 42;
    });

    auto future2 = activeObject.enqueue([]() {
        std::cout << "Task 2 executed." << std::endl;
        return 100;
    });

    //std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Result of Task 1: " << future1.get() << std::endl;
    std::cout << "Result of Task 2: " << future2.get() << std::endl;

    return 0;
}
