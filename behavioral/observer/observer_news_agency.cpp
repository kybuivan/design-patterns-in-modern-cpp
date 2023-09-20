#include <iostream>
#include <string>
#include <vector>

class Observer
{
public:
    virtual void update(const std::string &news) = 0;
};

class Subscriber : public Observer
{
private:
    std::string name;

public:
    Subscriber(const std::string &n) : name(n)
    {
    }

    void update(const std::string &news) override
    {
        std::cout << "Subscriber " << name << " received news: " << news << std::endl;
    }
};

class Observable
{
private:
    std::vector<Observer *> observers;

public:
    void addObserver(Observer *observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(Observer *observer)
    {
        for (auto it = observers.begin(); it != observers.end(); ++it)
        {
            if (*it == observer)
            {
                observers.erase(it);
                break;
            }
        }
    }

    void notifyObservers(const std::string &news)
    {
        for (auto observer : observers)
        {
            observer->update(news);
        }
    }
};

class NewsPublisher : public Observable
{
public:
    void publishNews(const std::string &news)
    {
        std::cout << "Publishing news: " << news << std::endl;
        notifyObservers(news);
    }
};

int main()
{
    NewsPublisher businessNewsPublisher;

    Subscriber subscriber1("Subscriber 1");
    Subscriber subscriber2("Subscriber 2");

    businessNewsPublisher.addObserver(&subscriber1);
    businessNewsPublisher.addObserver(&subscriber2);

    businessNewsPublisher.publishNews("New business regulations announced!");

    businessNewsPublisher.removeObserver(&subscriber1);

    businessNewsPublisher.publishNews("Stock market reaches a new high!");

    return 0;
}
