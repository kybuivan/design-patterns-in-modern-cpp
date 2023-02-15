#include <iostream>
#include <vector>

class Iterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual int currentItem() = 0;
};

class ConcreteIterator : public Iterator {
private:
    std::vector<int> items;
    int current = 0;

public:
    ConcreteIterator(std::vector<int> &vec) : items(vec) {}

    void first() { current = 0; }

    void next() { current++; }

    bool isDone() { return current >= items.size(); }

    int currentItem() { return items[current]; }
};

class Aggregate {
public:
    virtual Iterator *createIterator() = 0;
};

class ConcreteAggregate : public Aggregate {
private:
    std::vector<int> items;

public:
    ConcreteAggregate() {}

    void addItem(int item) { items.push_back(item); }

    Iterator *createIterator() { return new ConcreteIterator(items); }
};

int main() {
    ConcreteAggregate a;
    a.addItem(1);
    a.addItem(2);
    a.addItem(3);
    a.addItem(4);
    a.addItem(5);

    Iterator *iter = a.createIterator();

    for (iter->first(); !iter->isDone(); iter->next()) {
        std::cout << iter->currentItem() << std::endl;
    }

    return 0;
}
