#include <iostream>
#include <memory>
#include <vector>

// Forward declaration of IIterator interface
class IIterator;

// Forward declaration of IContainer interface
class IContainer;

// IIterator interface
class IIterator
{
public:
    virtual bool hasNext() = 0;
    virtual std::string next() = 0;
};

// IContainer interface
class IContainer
{
public:
    virtual std::shared_ptr<IIterator> createIterator() = 0;
};

// BooksCollection class implementing IContainer
class BooksCollection : public IContainer
{
private:
    std::vector<std::string> titles = {"Design Patterns", "1", "2", "3", "4"};

public:
    std::shared_ptr<IIterator> createIterator() override
    {
        return std::make_shared<BookIterator>(*this);
    }

    // Nested BookIterator class implementing IIterator
    class BookIterator : public IIterator
    {
    private:
        BooksCollection &collection;
        int position;

    public:
        BookIterator(BooksCollection &container) : collection(container), position(0)
        {
        }

        bool hasNext() override
        {
            return position < collection.titles.size();
        }

        std::string next() override
        {
            if (hasNext())
            {
                return collection.titles[position++];
            }
            else
            {
                return "";
            }
        }
    };
};

int main()
{
    BooksCollection bookCollection;
    std::shared_ptr<IIterator> iterator = bookCollection.createIterator();

    while (iterator->hasNext())
    {
        std::cout << iterator->next() << std::endl;
    }

    return 0;
}
