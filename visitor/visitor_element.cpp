#include <iostream>
#include <vector>

class Visitor;

class Element {
public:
    virtual void accept(Visitor& v) = 0;
};

class ConcreteElementA : public Element {
public:
    void accept(Visitor& v);
    std::string operationA();
};

class ConcreteElementB : public Element {
public:
    void accept(Visitor& v);
    int operationB();
};

class Visitor {
public:
    virtual void visit(ConcreteElementA& e) = 0;
    virtual void visit(ConcreteElementB& e) = 0;
};

class ConcreteVisitor1 : public Visitor {
public:
    void visit(ConcreteElementA& e);
    void visit(ConcreteElementB& e);
};

class ConcreteVisitor2 : public Visitor {
public:
    void visit(ConcreteElementA& e);
    void visit(ConcreteElementB& e);
};

void ConcreteElementA::accept(Visitor& v) {
    v.visit(*this);
}

std::string ConcreteElementA::operationA() {
    return "ConcreteElementA operation";
}

void ConcreteElementB::accept(Visitor& v) {
    v.visit(*this);
}

int ConcreteElementB::operationB() {
    return 42;
}

void ConcreteVisitor1::visit(ConcreteElementA& e) {
    std::cout << "ConcreteVisitor1 visited " << e.operationA() << std::endl;
}

void ConcreteVisitor1::visit(ConcreteElementB& e) {
    std::cout << "ConcreteVisitor1 visited " << e.operationB() << std::endl;
}

void ConcreteVisitor2::visit(ConcreteElementA& e) {
    std::cout << "ConcreteVisitor2 visited " << e.operationA() << std::endl;
}

void ConcreteVisitor2::visit(ConcreteElementB& e) {
    std::cout << "ConcreteVisitor2 visited " << e.operationB() << std::endl;
}

int main() {
    std::vector<Element*> elements = {new ConcreteElementA(), new ConcreteElementB()};
    std::vector<Visitor*> visitors = {new ConcreteVisitor1(), new ConcreteVisitor2()};
    for (Element* e : elements) {
        for (Visitor* v : visitors) {
            e->accept(*v);
        }
    }
    return 0;
}
