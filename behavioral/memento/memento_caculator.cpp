#include <iostream>

// Memento interface to Caretaker
class PreviousCalculationToCareTaker
{
public:
    virtual ~PreviousCalculationToCareTaker() = default;
};

// Memento to Originator interface
class PreviousCalculationToOriginator
{
public:
    virtual int getFirstNumber() const = 0;
    virtual int getSecondNumber() const = 0;
    virtual ~PreviousCalculationToOriginator() = default;
};

// Memento Implementation
class PreviousCalculationImp : public PreviousCalculationToCareTaker, public PreviousCalculationToOriginator
{
private:
    int firstNumber;
    int secondNumber;

public:
    PreviousCalculationImp(int first, int second) : firstNumber(first), secondNumber(second)
    {
    }

    int getFirstNumber() const override
    {
        return firstNumber;
    }

    int getSecondNumber() const override
    {
        return secondNumber;
    }
};

// Calculator interface (Originator)
class Calculator
{
public:
    virtual PreviousCalculationToCareTaker *backupLastCalculation() = 0;
    virtual void restorePreviousCalculation(PreviousCalculationToCareTaker *memento) = 0;
    virtual int getCalculationResult() = 0;
    virtual void setFirstNumber(int first) = 0;
    virtual void setSecondNumber(int second) = 0;
    virtual ~Calculator() = default;
};

// Calculator Implementation
class CalculatorImp : public Calculator
{
private:
    int firstNumber;
    int secondNumber;

public:
    PreviousCalculationToCareTaker *backupLastCalculation() override
    {
        return new PreviousCalculationImp(firstNumber, secondNumber);
    }

    int getCalculationResult() override
    {
        return firstNumber + secondNumber;
    }

    void restorePreviousCalculation(PreviousCalculationToCareTaker *memento) override
    {
        PreviousCalculationImp *prevCalculation = dynamic_cast<PreviousCalculationImp *>(memento);
        if (prevCalculation)
        {
            firstNumber = prevCalculation->getFirstNumber();
            secondNumber = prevCalculation->getSecondNumber();
        }
    }

    void setFirstNumber(int first) override
    {
        firstNumber = first;
    }

    void setSecondNumber(int second) override
    {
        secondNumber = second;
    }
};

int main()
{
    Calculator *calculator = new CalculatorImp();

    calculator->setFirstNumber(10);
    calculator->setSecondNumber(100);
    std::cout << "Result: " << calculator->getCalculationResult() << std::endl;

    PreviousCalculationToCareTaker *memento = calculator->backupLastCalculation();

    calculator->setFirstNumber(17);
    calculator->setSecondNumber(-290);
    std::cout << "Result: " << calculator->getCalculationResult() << std::endl;

    calculator->restorePreviousCalculation(memento);
    std::cout << "Restored Result: " << calculator->getCalculationResult() << std::endl;

    delete calculator;
    delete memento;

    return 0;
}
