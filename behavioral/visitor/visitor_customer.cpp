#include <algorithm>
#include <iostream>
#include <vector>

// Concrete Visitable Classes
class Item;
class Order;
class Customer;

// Abstract Visitor Interface
class IVisitor
{
public:
    virtual void visit(class Customer &customer) = 0;
    virtual void visit(class Order &order) = 0;
    virtual void visit(class Item &item) = 0;
};

// Abstract Visitable Interface
class IVisitable
{
public:
    virtual void accept(IVisitor &visitor) = 0;
};

class Item : public IVisitable
{
private:
    std::string name;

public:
    Item(const std::string &n) : name(n)
    {
    }

    void accept(IVisitor &visitor) override
    {
        visitor.visit(*this);
    }

    std::string getName() const
    {
        return name;
    }
};

class Order : public IVisitable
{
private:
    std::string name;
    std::vector<Item> items;

public:
    Order(const std::string &n) : name(n)
    {
    }

    void accept(IVisitor &visitor) override
    {
        visitor.visit(*this);
        for (auto &item : items)
        {
            item.accept(visitor);
        }
    }

    std::string getName() const
    {
        return name;
    }

    void addItem(const Item &item)
    {
        items.push_back(item);
    }
};

class Customer : public IVisitable
{
private:
    std::string name;
    std::vector<Order> orders;

public:
    Customer(const std::string &n) : name(n)
    {
    }

    void accept(IVisitor &visitor) override
    {
        visitor.visit(*this);
        for (auto &order : orders)
        {
            order.accept(visitor);
        }
    }

    std::string getName() const
    {
        return name;
    }

    void addOrder(const Order &order)
    {
        orders.push_back(order);
    }
};

// Concrete Visitor
class GeneralReport : public IVisitor
{
private:
    int customersNo = 0;
    int ordersNo = 0;
    int itemsNo = 0;

public:
    void visit(class Customer &customer) override
    {
        std::cout << customer.getName() << std::endl;
        customersNo++;
    }

    void visit(class Order &order) override
    {
        std::cout << order.getName() << std::endl;
        ordersNo++;
    }

    void visit(class Item &item) override
    {
        std::cout << item.getName() << std::endl;
        itemsNo++;
    }

    void displayResults()
    {
        std::cout << "Nr of customers: " << customersNo << std::endl;
        std::cout << "Nr of orders: " << ordersNo << std::endl;
        std::cout << "Nr of items: " << itemsNo << std::endl;
    }
};

int main()
{
    Customer c1("customer1");
    c1.addOrder(Order(".order1"));
    c1.addOrder(Order(".order2"));
    c1.addOrder(Order(".order3"));

    Customer c2("customer2");
    Order o(".order_a");
    o.addItem(Item("..item_a1"));
    o.addItem(Item("..item_a2"));
    o.addItem(Item("..item_a3"));
    c2.addOrder(o);
    c2.addOrder(Order(".order_b"));

    std::vector<Customer> customers = {c1, c2};

    GeneralReport visitor;

    for (auto &customer : customers)
    {
        customer.accept(visitor);
    }

    visitor.displayResults();

    return 0;
}
