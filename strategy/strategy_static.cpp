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
    virtual void add_list_item(std::ostringstream &oss, const std::string &item) = 0;
    virtual void start(std::ostringstream &oss) = 0;
    virtual void end(std::ostringstream &oss) = 0;
};

struct MarkdownListStrategy : ListStrategy
{
    void start(std::ostringstream &oss) override
    {
    }

    void end(std::ostringstream &oss) override
    {
    }

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

template <typename LS>
struct TextProcessor
{
    void clear()
    {
        oss.str("");
        oss.clear();
    }
    void append_list(const std::vector<std::string> items)
    {
        list_strategy.start(oss);
        for (auto &item : items)
            list_strategy.add_list_item(oss, item);
        list_strategy.end(oss);
    }
    std::string str() const
    {
        return oss.str();
    }

private:
    std::ostringstream oss;
    LS list_strategy;
};

int main()
{
    // markdown
    TextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list({"foo", "bar", "baz"});
    std::cout << tpm.str() << std::endl;

    // html
    TextProcessor<HtmlListStrategy> tph;
    tph.append_list({"foo", "bar", "baz"});
    std::cout << tph.str() << std::endl;

    return 0;
}
