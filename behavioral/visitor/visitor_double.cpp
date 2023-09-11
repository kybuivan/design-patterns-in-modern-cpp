#include <iostream>
#include <memory>
#include <sstream>
#include <string>

struct SubtractionExpression;
struct DoubleExpression;
struct AdditionExpression;

struct ExpressionVisitor
{
    virtual ~ExpressionVisitor() = default;
    virtual void visit(DoubleExpression &de) = 0;
    virtual void visit(AdditionExpression &ae) = 0;
    virtual void visit(SubtractionExpression &se) = 0;
};

struct ExpressionPrinter : ExpressionVisitor
{
    std::ostringstream oss;

    std::string str() const
    {
        return oss.str();
    }

    void visit(DoubleExpression &de) override;
    void visit(AdditionExpression &ae) override;
    void visit(SubtractionExpression &se) override;
};

struct ExpressionEvaluator : ExpressionVisitor
{
    double result;

    void visit(DoubleExpression &de) override;
    void visit(AdditionExpression &ae) override;
    void visit(SubtractionExpression &se) override;
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
        : left(std::move(left)), right(std::move(right))
    {
    }

    void accept(ExpressionVisitor &visitor) override
    {
        visitor.visit(*this);
    }
};

struct SubtractionExpression : Expression
{
    std::unique_ptr<Expression> left, right;

    SubtractionExpression(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right))
    {
    }

    void accept(ExpressionVisitor &visitor) override
    {
        visitor.visit(*this);
    }
};

void ExpressionPrinter::visit(DoubleExpression &de)
{
    oss << de.value;
}

void ExpressionPrinter::visit(AdditionExpression &ae)
{
    bool need_braces = dynamic_cast<SubtractionExpression *>(ae.right.get());
    ae.left->accept(*this);
    oss << "-";
    if (need_braces)
        oss << "(";
    ae.right->accept(*this);
    if (need_braces)
        oss << ")";
}

void ExpressionPrinter::visit(SubtractionExpression &se)
{
    bool need_braces = dynamic_cast<SubtractionExpression *>(se.right.get());
    if (need_braces)
        oss << "(";
    se.left->accept(*this);
    oss << "-";
    se.right->accept(*this);
    if (need_braces)
        oss << ")";
}

void ExpressionEvaluator::visit(DoubleExpression &de)
{
    result = de.value;
}

void ExpressionEvaluator::visit(AdditionExpression &ae)
{
    ae.left->accept(*this);
    auto temp = result;
    ae.right->accept(*this);
    result += temp;
}

void ExpressionEvaluator::visit(SubtractionExpression &se)
{
    se.left->accept(*this);
    auto temp = result;
    se.right->accept(*this);
    result = temp - result;
}

int main()
{
    auto e = std::make_unique<AdditionExpression>(
        std::make_unique<DoubleExpression>(1),
        std::make_unique<SubtractionExpression>(std::make_unique<DoubleExpression>(2),
                                                std::make_unique<DoubleExpression>(3)));

    ExpressionPrinter printer;
    ExpressionEvaluator evaluator;
    e->accept(printer);
    e->accept(evaluator);
    std::cout << printer.str() << " = " << evaluator.result << std::endl;

    return 0;
}
