#include <iostream>
#include <memory>
#include <sstream>
#include <string>

struct Expression
{
    virtual ~Expression() = default;
};

struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(const double value) : value{value}
    {
    }
};

struct AdditionExpression : Expression
{
    std::unique_ptr<Expression> left, right;

    AdditionExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right))
    {
    }
};

struct ExpressionPrinter
{
    std::ostringstream oss;

    void print(const Expression *e)
    {
        if (const auto de = dynamic_cast<const DoubleExpression *>(e))
        {
            oss << de->value;
        }
        else if (const auto ae = dynamic_cast<const AdditionExpression *>(e))
        {
            oss << "(";
            print(ae->left.get());
            oss << "+";
            print(ae->right.get());
            oss << ")";
        }
    }

    std::string str() const
    {
        return oss.str();
    }
};

int main()
{
    auto e = std::make_unique<AdditionExpression>(
        std::make_unique<DoubleExpression>(1),
        std::make_unique<AdditionExpression>(std::make_unique<DoubleExpression>(2),
                                             std::make_unique<DoubleExpression>(3)));

    ExpressionPrinter ep;
    ep.print(e.get());
    std::cout << ep.str() << std::endl;

    return 0;
}
