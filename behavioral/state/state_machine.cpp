#include <iostream>
#include <string>
using namespace std;

// Forward declaration
class VendingMachine;

// Abstract state class
class State
{
public:
    virtual ~State() = default;

    virtual void insertCoin(VendingMachine &machine) = 0;
    virtual void ejectCoin(VendingMachine &machine) = 0;
    virtual void selectProduct(VendingMachine &machine) = 0;
    virtual void dispenseProduct(VendingMachine &machine) = 0;
    virtual string toString() const = 0;
};

// Concrete state class: Ready
class ReadyState : public State
{
public:
    virtual void insertCoin(VendingMachine &machine);
    virtual void ejectCoin(VendingMachine &machine);
    virtual void selectProduct(VendingMachine &machine);
    virtual void dispenseProduct(VendingMachine &machine);
    virtual string toString() const
    {
        return "Ready state";
    }
};

// Concrete state class: CoinInserted
class CoinInsertedState : public State
{
public:
    virtual void insertCoin(VendingMachine &machine);
    virtual void ejectCoin(VendingMachine &machine);
    virtual void selectProduct(VendingMachine &machine);
    virtual void dispenseProduct(VendingMachine &machine);
    virtual string toString() const
    {
        return "Coin inserted state";
    }
};

// Concrete state class: ProductSelected
class ProductSelectedState : public State
{
public:
    virtual void insertCoin(VendingMachine &machine);
    virtual void ejectCoin(VendingMachine &machine);
    virtual void selectProduct(VendingMachine &machine);
    virtual void dispenseProduct(VendingMachine &machine);
    virtual string toString() const
    {
        return "Product selected state";
    }
};

// Concrete state class: ProductDispensed
class ProductDispensedState : public State
{
public:
    virtual void insertCoin(VendingMachine &machine);
    virtual void ejectCoin(VendingMachine &machine);
    virtual void selectProduct(VendingMachine &machine);
    virtual void dispenseProduct(VendingMachine &machine);
    virtual string toString() const
    {
        return "Product dispensed state";
    }
};

// The context class: VendingMachine
class VendingMachine
{
public:
    VendingMachine(int productCount);
    void insertCoin();
    void ejectCoin();
    void selectProduct();
    void dispenseProduct();
    void setState(State *state);
    int getProductCount() const
    {
        return m_productCount;
    }
    void setProductCount(int productCount)
    {
        m_productCount = productCount;
    }
    State *getReadyState() const
    {
        return m_readyState;
    }
    State *getCoinInsertedState() const
    {
        return m_coinInsertedState;
    }
    State *getProductSelectedState() const
    {
        return m_productSelectedState;
    }
    State *getProductDispensedState() const
    {
        return m_productDispensedState;
    }
    State *getState() const
    {
        return m_currentState;
    }

private:
    State *m_currentState;
    State *m_readyState;
    State *m_coinInsertedState;
    State *m_productSelectedState;
    State *m_productDispensedState;
    int m_productCount;
};

// State implementations
void ReadyState::insertCoin(VendingMachine &machine)
{
    cout << "You inserted a coin." << endl;
    machine.setState(machine.getCoinInsertedState());
}

void ReadyState::ejectCoin(VendingMachine &machine)
{
    cout << "You haven't inserted a coin." << endl;
}

void ReadyState::selectProduct(VendingMachine &machine)
{
    cout << "You haven't inserted a coin." << endl;
}

void ReadyState::dispenseProduct(VendingMachine &machine)
{
    cout << "You haven't inserted a coin." << endl;
}

void CoinInsertedState::insertCoin(VendingMachine &machine)
{
    cout << "You inserted another coin." << endl;
}

void CoinInsertedState::ejectCoin(VendingMachine &machine)
{
    cout << "Coin returned." << endl;
    machine.setState(machine.getReadyState());
}

void CoinInsertedState::selectProduct(VendingMachine &machine)
{
    cout << "You selected a product." << endl;
    machine.setState(machine.getProductSelectedState());
}

void CoinInsertedState::dispenseProduct(VendingMachine &machine)
{
    cout << "You need to select a product first." << endl;
}

void ProductSelectedState::insertCoin(VendingMachine &machine)
{
    cout << "You can't insert another coin." << endl;
}

void ProductSelectedState::ejectCoin(VendingMachine &machine)
{
    cout << "Coin returned." << endl;
    machine.setState(machine.getCoinInsertedState());
}

void ProductSelectedState::selectProduct(VendingMachine &machine)
{
    cout << "Product already selected." << endl;
}

void ProductSelectedState::dispenseProduct(VendingMachine &machine)
{
    cout << "Product dispensed." << endl;
    machine.setProductCount(machine.getProductCount() - 1);
    if (machine.getProductCount() == 0)
    {
        cout << "Machine is out of products." << endl;
        machine.setState(machine.getReadyState());
    }
    else
    {
        machine.setState(machine.getProductDispensedState());
    }
}

void ProductDispensedState::insertCoin(VendingMachine &machine)
{
    cout << "Please wait, we're already giving you a product." << endl;
}

void ProductDispensedState::ejectCoin(VendingMachine &machine)
{
    cout << "Sorry, you already got your product." << endl;
}

void ProductDispensedState::selectProduct(VendingMachine &machine)
{
    cout << "Product already dispensed." << endl;
}

void ProductDispensedState::dispenseProduct(VendingMachine &machine)
{
    cout << "No product dispensed." << endl;
}

// Context implementation
VendingMachine::VendingMachine(int productCount) : m_productCount(productCount)
{
    m_readyState = new ReadyState;
    m_coinInsertedState = new CoinInsertedState;
    m_productSelectedState = new ProductSelectedState;
    m_productDispensedState = new ProductDispensedState;
    m_currentState = m_readyState;
}

void VendingMachine::insertCoin()
{
    m_currentState->insertCoin(*this);
}

void VendingMachine::ejectCoin()
{
    m_currentState->ejectCoin(*this);
}

void VendingMachine::selectProduct()
{
    m_currentState->selectProduct(*this);
}

void VendingMachine::dispenseProduct()
{
    m_currentState->dispenseProduct(*this);
}

void VendingMachine::setState(State *state)
{
    m_currentState = state;
}

int main()
{
    // Create a vending machine with 3 products
    VendingMachine vendingMachine(3);

    // Print the current state of the machine
    cout << "Current state: " << vendingMachine.getState()->toString() << endl;

    // Insert a coin
    vendingMachine.insertCoin();

    // Print the current state of the machine
    cout << "Current state: " << vendingMachine.getState()->toString() << endl;

    // Eject the coin
    vendingMachine.ejectCoin();

    // Print the current state of the machine
    cout << "Current state: " << vendingMachine.getState()->toString() << endl;

    // Try to select a product without inserting a coin
    vendingMachine.selectProduct();

    // Insert a coin
    vendingMachine.insertCoin();

    // Try to select a product
    vendingMachine.selectProduct();

    // Print the current state of the machine
    cout << "Current state: " << vendingMachine.getState()->toString() << endl;

    // Dispense the product
    vendingMachine.dispenseProduct();

    // Print the current state of the machine
    cout << "Current state: " << vendingMachine.getState()->toString() << endl;

    // Try to dispense another product without inserting another coin
    vendingMachine.dispenseProduct();

    // Insert another coin
    vendingMachine.insertCoin();

    // Select another product
    vendingMachine.selectProduct();

    // Dispense the product
    vendingMachine.dispenseProduct();

    // Print the current state of the machine
    cout << "Current state: " << vendingMachine.getState()->toString() << endl;

    // Try to dispense another product, but the machine is out of products
    vendingMachine.dispenseProduct();

    // Print the current state of the machine
    cout << "Current state: " << vendingMachine.getState()->toString() << endl;

    return 0;
}
