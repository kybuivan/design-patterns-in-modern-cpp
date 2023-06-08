# Visitor Design Pattern
Visitor is a behavioral design pattern that lets you separate algorithms from the objects on which they operate.

## Overview
## Advantages
## Application
## Structure
```plantuml
@startuml

class Visitor {
    {abstract} +visitElementA(elementA: ElementA): void
    {abstract} +visitElementB(elementB: ElementB): void
}

class ConcreteVisitor1 {
    +visitElementA(elementA: ElementA): void
    +visitElementB(elementB: ElementB): void
}

class ConcreteVisitor2 {
    +visitElementA(elementA: ElementA): void
    +visitElementB(elementB: ElementB): void
}

interface Element {
    {abstract} +accept(visitor: Visitor): void
}

class ElementA {
    +accept(visitor: Visitor): void
}

class ElementB {
    +accept(visitor: Visitor): void
}

Visitor <|-- ConcreteVisitor1
Visitor <|-- ConcreteVisitor2
Element <|.. ElementA
Element <|.. ElementB
Visitor o-- Element

@enduml
```
## Code Examples
```cpp
struct Point
{
    double x;
    double y;
};

enum ShapeType
{
    circle,
    square
};

class Shape
{
protected:
    explicit Shape( ShapeType type )
    : type_( type )
    {}
public:
    virtual ~Shape() = default;
    ShapeType getType() const { return type_; }
private:
    ShapeType type_;
};
```
## Related design patterns
## External links
- [https://refactoring.guru/design-patterns/visitor](https://refactoring.guru/design-patterns/visitor)
- [https://en.wikipedia.org/wiki/Visitor_pattern](https://en.wikipedia.org/wiki/Visitor_pattern)
