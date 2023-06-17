#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <string>

class Observer
{
public:
    virtual ~Observer()
    {
    }
    virtual void update(const std::string &message) = 0;
};

class Subject
{
public:
    virtual ~Subject()
    {
    }
    virtual void registerObserver(std::weak_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::weak_ptr<Observer> observer) = 0;
    virtual void notifyObservers(const std::string &message) = 0;
};

class NewsAgency : public Subject
{
public:
    void registerObserver(std::weak_ptr<Observer> observer) override
    {
        observers_.push_back(observer);
    }

    void removeObserver(std::weak_ptr<Observer> observer) override
    {
        auto it = std::find_if(observers_.begin(),
                               observers_.end(),
                               [&observer](const std::weak_ptr<Observer> &wp) {
                                   return !wp.expired() && wp.lock() == observer.lock();
                               });

        if (it != observers_.end())
        {
            observers_.erase(it);
        }
    }

    void notifyObservers(const std::string &message) override
    {
        for (auto &weakObserver : observers_)
        {
            auto observer = weakObserver.lock();
            if (observer)
            {
                observer->update(message);
            }
        }
    }

    void addNews(const std::string &news)
    {
        news_ = news;
        notifyObservers(news_);
    }

private:
    std::list<std::weak_ptr<Observer>> observers_;
    std::string news_;
};

class TVChannel : public Observer
{
public:
    explicit TVChannel(const std::string &name) : name_(name)
    {
    }

    void update(const std::string &message) override
    {
        std::cout << name_ << " received news: " << message << std::endl;
    }

private:
    std::string name_;
};

int main()
{
    std::shared_ptr<NewsAgency> newsAgency = std::make_shared<NewsAgency>();

    std::shared_ptr<TVChannel> cnn = std::make_shared<TVChannel>("CNN");
    std::shared_ptr<TVChannel> bbc = std::make_shared<TVChannel>("BBC");
    std::shared_ptr<TVChannel> fox = std::make_shared<TVChannel>("FOX");

    newsAgency->registerObserver(cnn);
    newsAgency->registerObserver(bbc);
    newsAgency->registerObserver(fox);

    newsAgency->addNews("COVID-19 vaccine rollout begins");
    newsAgency->removeObserver(fox);
    newsAgency->addNews("Stock market hits record high");

    return 0;
}
