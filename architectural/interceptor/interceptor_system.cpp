#include <iostream>
#include <string>
#include <vector>

// Abstract Interceptor Class
class Interceptor
{
public:
    virtual void intercept(std::string &trade) = 0;
};

// Concrete Interceptors
class RuleEnforcementInterceptor : public Interceptor
{
public:
    void intercept(std::string &trade) override
    {
        std::cout << "Rule Enforcement: Checking trade compliance." << std::endl;
        // Simulate trade rule enforcement logic
        if (trade.find("restricted") != std::string::npos)
        {
            std::cout << "Rule Enforcement: Trade violates restrictions." << std::endl;
            trade = "Rejected: " + trade;
        }
    }
};

class TransactionLoggingInterceptor : public Interceptor
{
public:
    void intercept(std::string &trade) override
    {
        std::cout << "Transaction Logging: Recording trade details." << std::endl;
        // Simulate transaction logging
        std::cout << "Transaction Logging: Trade logged: " << trade << std::endl;
    }
};

class FeeCalculationInterceptor : public Interceptor
{
public:
    void intercept(std::string &trade) override
    {
        std::cout << "Fee Calculation: Calculating transaction fees." << std::endl;
        // Simulate fee calculation logic
        double fee = trade.length() * 0.01;
        std::cout << "Fee Calculation: Transaction fee: $" << fee << std::endl;
    }
};

// Client (Handler)
class TradingSystem
{
private:
    std::vector<Interceptor *> interceptors;

public:
    TradingSystem()
    {
        // Configure interceptors
        interceptors.push_back(new RuleEnforcementInterceptor());
        interceptors.push_back(new TransactionLoggingInterceptor());
        interceptors.push_back(new FeeCalculationInterceptor());
    }

    void executeTrade(std::string &trade)
    {
        // Execute interceptors in the order they are defined
        for (Interceptor *interceptor : interceptors)
        {
            interceptor->intercept(trade);
        }

        // Core trade execution logic goes here
        std::cout << "Trading System: Executing trade: " << trade << std::endl;
    }
};

int main()
{
    TradingSystem tradingSystem;

    std::string trade1 = "Buy AAPL";
    std::string trade2 = "Sell restricted stock";

    tradingSystem.executeTrade(trade1);
    tradingSystem.executeTrade(trade2);

    return 0;
}
