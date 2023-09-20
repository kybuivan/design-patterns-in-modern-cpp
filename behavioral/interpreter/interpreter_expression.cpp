#include <iostream>
#include <map>
#include <memory>

class Expression
{
public:
    virtual int interpret(std::map<char, int> &context) = 0;
    virtual ~Expression()
    {
    }
};

class Number : public Expression
{
private:
    int value;

public:
    Number(int val) : value(val)
    {
    }

    int interpret(std::map<char, int> &context) override
    {
        return value;
    }
};

class Variable : public Expression
{
private:
    char name;

public:
    Variable(char varName) : name(varName)
    {
    }

    int interpret(std::map<char, int> &context) override
    {
        if (context.find(name) != context.end())
        {
            return context[name];
        }
        else
        {
            std::cerr << "Variable " << name << " not found in context." << std::endl;
            return 0; // Default value
        }
    }
};

class Add : public Expression
{
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

public:
    Add(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : left(l), right(r)
    {
    }

    int interpret(std::map<char, int> &context) override
    {
        return left->interpret(context) + right->interpret(context);
    }
};

class Subtract : public Expression
{
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

public:
    Subtract(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) : left(l), right(r)
    {
    }

    int interpret(std::map<char, int> &context) override
    {
        return left->interpret(context) - right->interpret(context);
    }
};

int main()
{
    std::map<char, int> context;
    context['x'] = 10;
    context['y'] = 5;

    std::shared_ptr<Expression> expression =
        std::make_shared<Add>(std::make_shared<Variable>('x'),
                              std::make_shared<Subtract>(std::make_shared<Variable>('y'), std::make_shared<Number>(2)));

    int result = expression->interpret(context);

    std::cout << "Result: " << result << std::endl;

    return 0;
}
