#include <iostream>
#include <memory>
#include <sstream>
#include <string>

struct DoubleExpression;
struct AdditionExpression;

struct ExpressionVisitor
{
    virtual ~ExpressionVisitor() = default;
    virtual void visit(DoubleExpression &de) = 0;
    virtual void visit(AdditionExpression &ae) = 0;
};

struct Expression
{
    virtual ~Expression() = default;

    virtual void accept(ExpressionVisitor &visitor) = 0;
};

struct DoubleExpression : Expression
{
    double value;

    explicit DoubleExpression(const double value) : value{value}
    {
    }

    void accept(ExpressionVisitor &visitor) override
    {
        visitor.visit(*this);
    }
};

struct AdditionExpression : Expression
{
    std::unique_ptr<Expression> left, right;

    AdditionExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left{std::move(left)}, right{std::move(right)}
    {
    }

    void accept(ExpressionVisitor &visitor) override
    {
        visitor.visit(*this);
    }
};

struct PrintExpressionVisitor : ExpressionVisitor
{
    std::ostringstream oss;

    void visit(DoubleExpression &de) override
    {
        oss << de.value;
    }

    void visit(AdditionExpression &ae) override
    {
        oss << "(";
        ae.left->accept(*this);
        oss << "+";
        ae.right->accept(*this);
        oss << ")";
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

    PrintExpressionVisitor visitor;
    e->accept(visitor);
    std::cout << visitor.str() << std::endl;

    return 0;
}
