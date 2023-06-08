#include <iostream>
#include <list>
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
    virtual void registerObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
    virtual void notifyObservers(const std::string &message) = 0;
};

class NewsAgency : public Subject
{
public:
    void registerObserver(Observer *observer) override
    {
        observers_.push_back(observer);
    }

    void removeObserver(Observer *observer) override
    {
        observers_.remove(observer);
    }

    void notifyObservers(const std::string &message) override
    {
        for (Observer *observer : observers_)
        {
            observer->update(message);
        }
    }

    void addNews(const std::string &news)
    {
        news_ = news;
        notifyObservers(news_);
    }

private:
    std::list<Observer *> observers_;
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
    NewsAgency newsAgency;

    TVChannel cnn("CNN");
    TVChannel bbc("BBC");
    TVChannel fox("FOX");

    newsAgency.registerObserver(&cnn);
    newsAgency.registerObserver(&bbc);
    newsAgency.registerObserver(&fox);

    newsAgency.addNews("COVID-19 vaccine rollout begins");
    newsAgency.removeObserver(&fox);
    newsAgency.addNews("Stock market hits record high");

    return 0;
}
