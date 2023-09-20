#include <iostream>
#include <memory>
#include <vector>

class Context
{
private:
    std::string input;
    int output;

public:
    Context(const std::string &input) : input(input), output(0)
    {
    }

    std::string getInput() const
    {
        return input;
    }

    void setInput(const std::string &input)
    {
        this->input = input;
    }

    int getOutput() const
    {
        return output;
    }

    void setOutput(int output)
    {
        this->output = output;
    }
};

class Expression
{
public:
    virtual void interpret(Context &context)
    {
        if (context.getInput().empty())
            return;

        if (context.getInput().find(nine()) == 0)
        {
            context.setOutput(context.getOutput() + (9 * multiplier()));
            context.setInput(context.getInput().substr(2));
        }
        else if (context.getInput().find(four()) == 0)
        {
            context.setOutput(context.getOutput() + (4 * multiplier()));
            context.setInput(context.getInput().substr(2));
        }
        else if (context.getInput().find(five()) == 0)
        {
            context.setOutput(context.getOutput() + (5 * multiplier()));
            context.setInput(context.getInput().substr(1));
        }

        while (context.getInput().find(one()) == 0)
        {
            context.setOutput(context.getOutput() + (1 * multiplier()));
            context.setInput(context.getInput().substr(1));
        }
    }

    virtual std::string one() = 0;
    virtual std::string four() = 0;
    virtual std::string five() = 0;
    virtual std::string nine() = 0;
    virtual int multiplier() = 0;
};

class ThousandExpression : public Expression
{
public:
    std::string one() override
    {
        return "M";
    }
    std::string four() override
    {
        return " ";
    }
    std::string five() override
    {
        return " ";
    }
    std::string nine() override
    {
        return " ";
    }
    int multiplier() override
    {
        return 1000;
    }
};

class HundredExpression : public Expression
{
public:
    std::string one() override
    {
        return "C";
    }
    std::string four() override
    {
        return "CD";
    }
    std::string five() override
    {
        return "D";
    }
    std::string nine() override
    {
        return "CM";
    }
    int multiplier() override
    {
        return 100;
    }
};

class TenExpression : public Expression
{
public:
    std::string one() override
    {
        return "X";
    }
    std::string four() override
    {
        return "XL";
    }
    std::string five() override
    {
        return "L";
    }
    std::string nine() override
    {
        return "XC";
    }
    int multiplier() override
    {
        return 10;
    }
};

class OneExpression : public Expression
{
public:
    std::string one() override
    {
        return "I";
    }
    std::string four() override
    {
        return "IV";
    }
    std::string five() override
    {
        return "V";
    }
    std::string nine() override
    {
        return "IX";
    }
    int multiplier() override
    {
        return 1;
    }
};

int main()
{
    std::string roman = "MCMXXVIII";
    Context context(roman);

    // Build the 'parse tree'
    std::vector<std::shared_ptr<Expression>> tree;
    tree.push_back(std::make_shared<ThousandExpression>());
    tree.push_back(std::make_shared<HundredExpression>());
    tree.push_back(std::make_shared<TenExpression>());
    tree.push_back(std::make_shared<OneExpression>());
    // Interpret
    for (auto it = tree.begin(); it != tree.end(); ++it)
    {
        auto exp = *it;
        exp->interpret(context);
    }

    std::cout << roman << " = " << context.getOutput() << std::endl;

    return 0;
}
