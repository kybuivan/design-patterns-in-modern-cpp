#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Context: Represents a data source or a collection of objects.
class Context
{
public:
    std::vector<std::string> data = {"Alice", "Bob", "Charlie", "David", "Eve"};
};

// Abstract Expression
class Expression
{
public:
    virtual std::vector<std::string> interpret(Context &context) = 0;
    virtual ~Expression()
    {
    }
};

// Terminal Expression: Represents a simple keyword to filter data.
class TerminalExpression : public Expression
{
private:
    std::string keyword;

public:
    TerminalExpression(const std::string &key) : keyword(key)
    {
    }

    std::vector<std::string> interpret(Context &context) override
    {
        std::vector<std::string> result;
        for (const std::string &item : context.data)
        {
            if (item.find(keyword) != std::string::npos)
            {
                result.push_back(item);
            }
        }
        return result;
    }
};

// Non-terminal Expression: Represents logical OR operation between expressions.
class OrExpression : public Expression
{
private:
    std::shared_ptr<Expression> expr1;
    std::shared_ptr<Expression> expr2;

public:
    OrExpression(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2) : expr1(e1), expr2(e2)
    {
    }

    std::vector<std::string> interpret(Context &context) override
    {
        std::vector<std::string> result = expr1->interpret(context);
        std::vector<std::string> secondResult = expr2->interpret(context);

        for (const std::string &item : secondResult)
        {
            if (std::find(result.begin(), result.end(), item) == result.end())
            {
                result.push_back(item);
            }
        }
        return result;
    }
};

// Non-terminal Expression: Represents logical AND operation between expressions.
class AndExpression : public Expression
{
private:
    std::shared_ptr<Expression> expr1;
    std::shared_ptr<Expression> expr2;

public:
    AndExpression(std::shared_ptr<Expression> e1, std::shared_ptr<Expression> e2) : expr1(e1), expr2(e2)
    {
    }

    std::vector<std::string> interpret(Context &context) override
    {
        std::vector<std::string> result = expr1->interpret(context);
        std::vector<std::string> secondResult = expr2->interpret(context);

        std::vector<std::string> intersection;
        for (const std::string &item : result)
        {
            if (std::find(secondResult.begin(), secondResult.end(), item) != secondResult.end())
            {
                intersection.push_back(item);
            }
        }
        return intersection;
    }
};

int main()
{
    Context context;

    // Define the query: (Alice OR Bob) AND (Charlie OR Eve)
    std::shared_ptr<Expression> query = std::make_shared<AndExpression>(
        std::make_shared<OrExpression>(std::make_shared<TerminalExpression>("Alice"), std::make_shared<TerminalExpression>("Bob")),
        std::make_shared<OrExpression>(std::make_shared<TerminalExpression>("Charlie"), std::make_shared<TerminalExpression>("Eve")));

    std::vector<std::string> result = query->interpret(context);

    std::cout << "Query result: ";
    for (const std::string &item : result)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}
