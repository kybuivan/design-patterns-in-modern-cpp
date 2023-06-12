// visitor examples for design patterns c++ book
#include <iostream>
#include <sstream>
#include <string>

struct Expression
{
    virtual void print(std::ostringstream &oss) = 0;
};

struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(const double value) : value{value}
    {
    }

    void print(std::ostringstream &oss) override
    {
        oss << value;
    }
};

struct AdditionExpression : Expression
{
    Expression *left, *right;

    AdditionExpression(Expression *const left, Expression *const right) : left{left}, right{right}
    {
    }

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }

    void print(std::ostringstream &oss) override
    {
        oss << "(";
        left->print(oss);
        oss << "+";
        right->print(oss);
        oss << ")";
    }
};

int main()
{
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};
    std::ostringstream oss;
    e->print(oss);
    std::cout << oss.str() << std::endl;

    return 0;
}
