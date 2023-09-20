#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Context
{
private:
    std::string input;

public:
    Context(const std::string &input) : input(input)
    {
    }

    std::string getInput() const
    {
        return input;
    }
};

class Expression
{
public:
    virtual bool interpret(Context &context) = 0;
};

class TerminalExpression : public Expression
{
private:
    std::string literal;

public:
    TerminalExpression(const std::string &str) : literal(str)
    {
    }

    bool interpret(Context &context) override
    {
        std::istringstream iss(context.getInput());
        std::string token;
        while (iss >> token)
        {
            if (token == literal)
            {
                return true;
            }
        }
        return false;
    }
};

class OrExpression : public Expression
{
private:
    std::shared_ptr<Expression> expression1;
    std::shared_ptr<Expression> expression2;

public:
    OrExpression(std::shared_ptr<Expression> exp1, std::shared_ptr<Expression> exp2) : expression1(exp1), expression2(exp2)
    {
    }

    bool interpret(Context &context) override
    {
        return expression1->interpret(context) || expression2->interpret(context);
    }
};

class AndExpression : public Expression
{
private:
    std::shared_ptr<Expression> expression1;
    std::shared_ptr<Expression> expression2;

public:
    AndExpression(std::shared_ptr<Expression> exp1, std::shared_ptr<Expression> exp2) : expression1(exp1), expression2(exp2)
    {
    }

    bool interpret(Context &context) override
    {
        return expression1->interpret(context) && expression2->interpret(context);
    }
};

std::shared_ptr<Expression> buildInterpreterTree()
{
    std::shared_ptr<Expression> terminal1 = std::make_shared<TerminalExpression>("John");
    std::shared_ptr<Expression> terminal2 = std::make_shared<TerminalExpression>("Henry");
    std::shared_ptr<Expression> terminal3 = std::make_shared<TerminalExpression>("Mary");
    std::shared_ptr<Expression> terminal4 = std::make_shared<TerminalExpression>("Owen");

    std::shared_ptr<Expression> alternation1 = std::make_shared<OrExpression>(terminal2, terminal3);
    std::shared_ptr<Expression> alternation2 = std::make_shared<OrExpression>(terminal1, alternation1);
    std::shared_ptr<Expression> define = std::make_shared<AndExpression>(terminal4, alternation2);

    return define;
}

int main()
{
    std::string context = "Mary Owen";

    Context inputContext(context);

    std::shared_ptr<Expression> define = buildInterpreterTree();

    std::cout << context << " is " << (define->interpret(inputContext) ? "true" : "false") << std::endl;

    return 0;
}
