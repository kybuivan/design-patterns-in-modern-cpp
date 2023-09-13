#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Book class representing individual books
class Book
{
public:
    Book(const std::string &title, const std::string &author) : title(title), author(author)
    {
    }

    std::string getTitle() const
    {
        return title;
    }

    std::string getAuthor() const
    {
        return author;
    }

private:
    std::string title;
    std::string author;
};

// Iterator interface
class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual Book next() = 0;
};

// Concrete Iterator for a collection of books
class BookIterator : public Iterator
{
public:
    BookIterator(std::vector<Book> &books) : books(books), position(0)
    {
    }

    bool hasNext() override
    {
        return position < books.size();
    }

    Book next() override
    {
        if (hasNext())
        {
            return books[position++];
        }
        else
        {
            throw std::out_of_range("No more books in the collection.");
        }
    }

private:
    std::vector<Book> &books;
    size_t position;
};

// Collection interface
class BookCollection
{
public:
    virtual std::shared_ptr<Iterator> createIterator() = 0;
};

// Concrete Collection for a library of books
class Library : public BookCollection
{
public:
    Library()
    {
        // Add some books to the library
        books.push_back(Book("The Great Gatsby", "F. Scott Fitzgerald"));
        books.push_back(Book("To Kill a Mockingbird", "Harper Lee"));
        books.push_back(Book("1984", "George Orwell"));
        books.push_back(Book("Pride and Prejudice", "Jane Austen"));
    }

    std::shared_ptr<Iterator> createIterator() override
    {
        return std::make_shared<BookIterator>(books);
    }

private:
    std::vector<Book> books;
};

int main()
{
    // Create a library and an iterator for it
    Library library;
    std::shared_ptr<Iterator> iterator = library.createIterator();

    // Traverse and print the books using the iterator
    while (iterator->hasNext())
    {
        Book book = iterator->next();
        std::cout << "Title: " << book.getTitle() << ", Author: " << book.getAuthor() << std::endl;
    }

    return 0;
}
