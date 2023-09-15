#include <iostream>
#include <memory>
#include <string>

class Document
{
public:
    Document(const std::string &content) : content_(content)
    {
    }

    const std::string &getContent() const
    {
        return content_;
    }

    void appendContent(const std::string &text)
    {
        content_ += text;
    }

private:
    std::string content_;
};

class DocumentProcessor
{
public:
    DocumentProcessor(std::shared_ptr<DocumentProcessor> next) : next_(next)
    {
    }

    virtual void process(std::shared_ptr<Document> document) = 0;

    void processNext(std::shared_ptr<Document> document)
    {
        if (next_)
        {
            next_->process(document);
        }
    }

private:
    std::shared_ptr<DocumentProcessor> next_;
};

class SpellChecker : public DocumentProcessor
{
public:
    SpellChecker(std::shared_ptr<DocumentProcessor> next) : DocumentProcessor(next)
    {
    }

    void process(std::shared_ptr<Document> document) override
    {
        std::cout << "Spell-checking the document." << std::endl;
        // Simulated spell-checking logic
        document->appendContent(" [Spell-checked]");
        processNext(document);
    }
};

class GrammarChecker : public DocumentProcessor
{
public:
    GrammarChecker(std::shared_ptr<DocumentProcessor> next) : DocumentProcessor(next)
    {
    }

    void process(std::shared_ptr<Document> document) override
    {
        std::cout << "Grammar-checking the document." << std::endl;
        // Simulated grammar-checking logic
        document->appendContent(" [Grammar-checked]");
        processNext(document);
    }
};

class Formatter : public DocumentProcessor
{
public:
    Formatter(std::shared_ptr<DocumentProcessor> next) : DocumentProcessor(next)
    {
    }

    void process(std::shared_ptr<Document> document) override
    {
        std::cout << "Formatting the document." << std::endl;
        // Simulated document formatting logic
        document->appendContent(" [Formatted]");
        processNext(document);
    }
};

int main()
{
    // Create a document and a chain of processors
    std::shared_ptr<Document> document = std::make_shared<Document>("Sample Document");
    std::shared_ptr<DocumentProcessor> formatter = std::make_shared<Formatter>(nullptr);
    std::shared_ptr<DocumentProcessor> grammarChecker = std::make_shared<GrammarChecker>(formatter);
    std::shared_ptr<DocumentProcessor> spellChecker = std::make_shared<SpellChecker>(grammarChecker);

    // Start processing
    spellChecker->process(document);

    // Display the final document content
    std::cout << "Final Document Content: " << document->getContent() << std::endl;

    return 0;
}
