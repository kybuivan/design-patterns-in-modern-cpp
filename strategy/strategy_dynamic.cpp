#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

enum class OutputFormat
{
    Markdown,
    Html
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;
    virtual void add_list_item(std::ostringstream &oss, const std::string &item){};
    virtual void start(std::ostringstream &oss){};
    virtual void end(std::ostringstream &oss){};
};

struct MarkdownListStrategy : ListStrategy
{
    void add_list_item(std::ostringstream &oss, const std::string &item) override
    {
        oss << " * " << item << std::endl;
    }
};

struct HtmlListStrategy : ListStrategy
{
    void start(std::ostringstream &oss) override
    {
        oss << "<ul>" << std::endl;
    }

    void end(std::ostringstream &oss) override
    {
        oss << "</ul>" << std::endl;
    }

    void add_list_item(std::ostringstream &oss, const std::string &item) override
    {
        oss << "<li>" << item << "</li>" << std::endl;
    }
};

struct TextProcessor
{
    void clear()
    {
        oss.str("");
        oss.clear();
    }
    void append_list(const std::vector<std::string> items)
    {
        list_strategy->start(oss);
        for (auto &item : items)
            list_strategy->add_list_item(oss, item);
        list_strategy->end(oss);
    }

    void set_output_format(const OutputFormat format)
    {
        switch (format)
        {
        case OutputFormat::Markdown:
            list_strategy = std::make_unique<MarkdownListStrategy>();
            break;
        case OutputFormat::Html:
            list_strategy = std::make_unique<HtmlListStrategy>();
            break;
        default:
            throw std::runtime_error("Unsupported strategy.");
        }
    }
    std::string str() const
    {
        return oss.str();
    }

private:
    std::ostringstream oss;
    std::unique_ptr<ListStrategy> list_strategy;
};

int main_()
{
    // markdown
    TextProcessor tp;
    tp.set_output_format(OutputFormat::Markdown);
    tp.append_list({"foo", "bar", "baz"});
    std::cout << tp.str() << std::endl;

    // html
    tp.clear();
    tp.set_output_format(OutputFormat::Html);
    tp.append_list({"foo", "bar", "baz"});
    std::cout << tp.str() << std::endl;

    return 0;
}
