#include <iostream>
#include <memory>
#include <string>

class Product
{
private:
    std::string partA;
    std::string partB;
    std::string partC;

public:
    void setPartA(const std::string &partA)
    {
        this->partA = partA;
    }

    void setPartB(const std::string &partB)
    {
        this->partB = partB;
    }

    void setPartC(const std::string &partC)
    {
        this->partC = partC;
    }

    void show()
    {
        std::cout << "Product Parts: " << partA << ", " << partB << ", " << partC << std::endl;
    }
};

class Builder
{
public:
    virtual ~Builder() = default;
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
    virtual std::unique_ptr<Product> getProduct() = 0;
};

class ConcreteBuilder1 : public Builder
{
private:
    std::unique_ptr<Product> product;

public:
    ConcreteBuilder1() : product(std::make_unique<Product>())
    {
    }

    void buildPartA() override
    {
        product->setPartA("PartA1");
    }

    void buildPartB() override
    {
        product->setPartB("PartB1");
    }

    void buildPartC() override
    {
        product->setPartC("PartC1");
    }

    std::unique_ptr<Product> getProduct() override
    {
        return std::move(product);
    }
};

class ConcreteBuilder2 : public Builder
{
private:
    std::unique_ptr<Product> product;

public:
    ConcreteBuilder2() : product(std::make_unique<Product>())
    {
    }

    void buildPartA() override
    {
        product->setPartA("PartA2");
    }

    void buildPartB() override
    {
        product->setPartB("PartB2");
    }

    void buildPartC() override
    {
        product->setPartC("PartC2");
    }

    std::unique_ptr<Product> getProduct() override
    {
        return std::move(product);
    }
};

class Director
{
private:
    Builder *builder;

public:
    void setBuilder(Builder *builder)
    {
        this->builder = builder;
    }

    void buildMinimalViableProduct()
    {
        builder->buildPartA();
    }

    void buildFullFeaturedProduct()
    {
        builder->buildPartA();
        builder->buildPartB();
        builder->buildPartC();
    }
};

int main()
{
    Director director;
    std::unique_ptr<Builder> builder1 = std::make_unique<ConcreteBuilder1>();
    std::unique_ptr<Builder> builder2 = std::make_unique<ConcreteBuilder2>();

    director.setBuilder(builder1.get());
    director.buildMinimalViableProduct();
    std::unique_ptr<Product> product1 = builder1->getProduct();
    product1->show();

    director.setBuilder(builder2.get());
    director.buildFullFeaturedProduct();
    std::unique_ptr<Product> product2 = builder2->getProduct();
    product2->show();

    return 0;
}
