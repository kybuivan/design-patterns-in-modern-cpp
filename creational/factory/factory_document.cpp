#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Abstract Document class
class Document
{
public:
    virtual void Open() = 0;
    virtual void Save(std::string filename) = 0;
    virtual void Close() = 0;
};

// Concrete HTMLDocument class
class HTMLDocument : public Document
{
public:
    void Open() override
    {
        std::cout << "Opening an HTML document." << std::endl;
    }

    void Save(std::string filename) override
    {
        std::cout << "Saving:" << filename << std::endl;
    }

    void Close() override
    {
        std::cout << "Close an HTML document." << std::endl;
    }
};

// Concrete MyDocument class
class MyDocument : public Document
{
public:
    void Open() override
    {
        std::cout << "Opening a MyDocument." << std::endl;
    }

    void Save(std::string filename) override
    {
        std::cout << "Saving:" << filename << std::endl;
    }

    void Close() override
    {
        std::cout << "Close a MyDocument." << std::endl;
    }
};

// Concrete MyDocument class
class PdfDocument : public Document
{
public:
    void Open() override
    {
        std::cout << "Opening a PdfDocument." << std::endl;
    }

    void Save(std::string filename) override
    {
        std::cout << "Saving:" << filename << std::endl;
    }

    void Close() override
    {
        std::cout << "Close a PdfDocument." << std::endl;
    }
};

// Application class
class Application
{
public:
    virtual std::shared_ptr<Document> CreateDocument(const std::string &type) = 0;

    void NewDocument(const std::string &type)
    {
        std::shared_ptr<Document> doc = CreateDocument(type);
        docs.push_back(doc);
        doc->Open();
        doc->Save(type);
        doc->Close();
    }

private:
    std::vector<std::shared_ptr<Document>> docs;
};

// MyApplication subclass
class MyApplication : public Application
{
public:
    std::shared_ptr<Document> CreateDocument(const std::string &type) override
    {
        if (type == "html")
            return std::make_shared<HTMLDocument>();
        if (type == "proprietary")
            return std::make_shared<MyDocument>();
        if (type == "pdf")
            return std::make_shared<PdfDocument>();
        return nullptr; // Return nullptr for unsupported types
    }
};

int main()
{
    std::shared_ptr<Application> app = std::make_shared<MyApplication>();

    app->NewDocument("html");
    app->NewDocument("proprietary");
    app->NewDocument("pdf");

    return 0;
}
