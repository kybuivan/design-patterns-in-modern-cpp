#include <iostream>
#include <memory>
#include <sstream>
#include <string>

template <typename Visitable>
struct Visitor
{
    virtual void visit(Visitable &obj) = 0;
};

struct VisitorBase // marker interface
{
    virtual ~VisitorBase() = default;
};

struct Expression
{
    virtual ~Expression() = default;

    virtual void accept(VisitorBase &obj)
    {
        if (auto ev = dynamic_cast<Visitor<Expression> *>(&obj))
            ev->visit(*this);
    }
};

struct DoubleExpression : Expression
{
    double value;

    DoubleExpression(double value) : value(value)
    {
    }

    void accept(VisitorBase &obj) override
    {
        if (auto ev = dynamic_cast<Visitor<DoubleExpression> *>(&obj))
            ev->visit(*this);
    }
};

struct AdditionExpression : Expression
{
    std::unique_ptr<Expression> left, right;

    AdditionExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right))
    {
    }

    void accept(VisitorBase &obj) override
    {
        if (auto ev = dynamic_cast<Visitor<AdditionExpression> *>(&obj))
            ev->visit(*this);
    }
};

struct ExpressionPrinter : VisitorBase,
                           Visitor<Expression>,
                           Visitor<DoubleExpression>,
                           Visitor<AdditionExpression>
{
    void visit(Expression &obj) override
    {
        // fallback?
    }

    void visit(DoubleExpression &obj) override
    {
        oss << obj.value;
    }

    void visit(AdditionExpression &obj) override
    {
        oss << "(";
        obj.left->accept(*this);
        oss << "+";
        obj.right->accept(*this);
        oss << ")";
    }

    std::string str() const
    {
        return oss.str();
    }

private:
    std::ostringstream oss;
};

int main()
{
    auto e = std::make_unique<AdditionExpression>(
        std::make_unique<DoubleExpression>(1),
        std::make_unique<AdditionExpression>(std::make_unique<DoubleExpression>(2),
                                             std::make_unique<DoubleExpression>(3)));

    ExpressionPrinter ep;
    e->accept(ep);
    std::cout << ep.str() << "\n";

    return 0;
}
