#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Portfolio;

// Observer base class
class PortfolioObserver
{
public:
    virtual void update(const Portfolio &portfolio) = 0;
};

// Data property representing a stock holding
class Stock
{
public:
    Stock(const std::string &symbol, double price, int quantity) : symbol_(symbol), price_(price), quantity_(quantity)
    {
    }

    double getPrice() const
    {
        return price_;
    }

    int getQuantity() const
    {
        return quantity_;
    }

    std::string getSymbol() const
    {
        return symbol_;
    }

    void setPrice(double new_price)
    {
        if (new_price != price_)
        {
            price_ = new_price;
        }
    }

    void setQuantity(int new_quantity)
    {
        if (new_quantity != quantity_)
        {
            quantity_ = new_quantity;
        }
    }

private:
    std::string symbol_;
    double price_;
    int quantity_;
};

// Portfolio class containing multiple stocks
class Portfolio
{
public:
    void addStock(std::shared_ptr<Stock> stock)
    {
        stocks_.push_back(stock);
    }

    void updateStockPrice(const std::string &symbol, double new_price)
    {
        for (auto &stock : stocks_)
        {
            if (stock->getPrice() != new_price && stock->getSymbol() == symbol)
            {
                stock->setPrice(new_price);
            }
        }
        notifyObservers();
    }

    void bindObserver(PortfolioObserver *observer)
    {
        observers_.push_back(observer);
    }

    const std::vector<std::shared_ptr<Stock>> &getStocks() const
    {
        return stocks_;
    }

private:
    std::vector<std::shared_ptr<Stock>> stocks_;
    std::vector<PortfolioObserver *> observers_;

    void notifyObservers()
    {
        for (auto &observer : observers_)
        {
            observer->update(*this);
        }
    }
};

// Dashboard observer displaying portfolio information
class Dashboard : public PortfolioObserver
{
public:
    Dashboard() : portfolio_(nullptr)
    {
    }

    void bindPortfolio(Portfolio *portfolio)
    {
        portfolio_ = portfolio;
        portfolio->bindObserver(this); // Pass a raw pointer
    }

    void update(const Portfolio &portfolio) override
    {
        displayPortfolio(portfolio);
    }

    void displayPortfolio(const Portfolio &portfolio)
    {
        std::cout << "Portfolio Summary:" << std::endl;
        const auto &stocks = portfolio.getStocks();
        for (const auto &stock : stocks)
        {
            std::cout << "Symbol: " << stock->getSymbol() << ", Quantity: " << stock->getQuantity()
                      << ", Price: " << stock->getPrice() << std::endl;
        }
        std::cout << "-----------------------------------------" << std::endl;
    }

private:
    Portfolio *portfolio_;
};

int main()
{
    auto portfolio = std::make_shared<Portfolio>();

    auto apple = std::make_shared<Stock>("AAPL", 150.0, 100);
    auto google = std::make_shared<Stock>("GOOGL", 2500.0, 50);

    portfolio->addStock(apple);
    portfolio->addStock(google);

    Dashboard dashboard;
    dashboard.bindPortfolio(portfolio.get()); // Pass a raw pointer

    // Simulate updating stock prices
    portfolio->updateStockPrice("AAPL", 155.0);
    portfolio->updateStockPrice("GOOGL", 2555.0);

    return 0;
}
