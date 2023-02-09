#include <iostream>
#include <string>
#include <vector>

class Product
{
private:
    std::string partA;
    std::string partB;
    std::string partC;

public:
    void setPartA(const std::string& partA)
    {
        this->partA = partA;
    }

    void setPartB(const std::string& partB)
    {
        this->partB = partB;
    }

    void setPartC(const std::string& partC)
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
    virtual ~Builder() {}
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual void buildPartC() = 0;
    virtual Product* getProduct() = 0;
};

class ConcreteBuilder1 : public Builder
{
private:
    Product* product;

public:
    ConcreteBuilder1()
    {
        product = new Product();
    }

    void buildPartA()
    {
        product->setPartA("PartA1");
    }

    void buildPartB()
    {
        product->setPartB("PartB1");
    }

    void buildPartC()
    {
        product->setPartC("PartC1");
    }

    Product* getProduct()
    {
        return product;
    }
};

class ConcreteBuilder2 : public Builder
{
private:
    Product* product;

public:
    ConcreteBuilder2()
    {
        product = new Product();
    }

    void buildPartA()
    {
        product->setPartA("PartA2");
    }

    void buildPartB()
    {
        product->setPartB("PartB2");
    }

    void buildPartC()
    {
        product->setPartC("PartC2");
    }

    Product* getProduct()
    {
        return product;
    }
};

class Director
{
private:
    Builder* builder;

public:
    void setBuilder(Builder* builder)
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
    Director* director = new Director();
    Builder* builder1 = new ConcreteBuilder1();
    Builder* builder2 = new ConcreteBuilder2();

    director->setBuilder(builder1);
    director->buildMinimalViableProduct();
    Product* product1 = builder1->getProduct();
    product1->show();

    director->setBuilder(builder2);
    director->buildFullFeaturedProduct();
    Product* product2 = builder2->getProduct();
	product2->show();
	
	delete product1;
	delete product2;
	delete builder1;
	delete builder2;
	delete director;

	return 0;
}
