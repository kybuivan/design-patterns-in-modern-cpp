#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

// Strategy interface
class ReportFormatter
{
public:
    virtual std::string formatReport(const std::vector<int> &data) const = 0;
    virtual ~ReportFormatter() = default;
};

// Concrete strategy classes
class CsvReportFormatter : public ReportFormatter
{
public:
    std::string formatReport(const std::vector<int> &data) const override
    {
        std::stringstream ss;
        for (auto d : data)
        {
            ss << d << ",";
        }
        return ss.str();
    }
};

class TabbedReportFormatter : public ReportFormatter
{
public:
    std::string formatReport(const std::vector<int> &data) const override
    {
        std::stringstream ss;
        for (auto d : data)
        {
            ss << d << "\t";
        }
        return ss.str();
    }
};

// Context class
class ReportGenerator
{
private:
    std::unique_ptr<ReportFormatter> formatter;

public:
    ReportGenerator(std::unique_ptr<ReportFormatter> formatter) : formatter(std::move(formatter))
    {
    }

    void setFormatter(std::unique_ptr<ReportFormatter> formatter)
    {
        this->formatter = std::move(formatter);
    }

    void generateReport(const std::vector<int> &data)
    {
        std::string formattedData = formatter->formatReport(data);
        std::cout << "Generated report: " << formattedData << std::endl;
    }
};

int main()
{
    std::vector<int> data = {1, 2, 3, 4, 5};

    std::unique_ptr<ReportFormatter> csvFormatter = std::make_unique<CsvReportFormatter>();
    std::unique_ptr<ReportFormatter> tabbedFormatter = std::make_unique<TabbedReportFormatter>();

    std::unique_ptr<ReportGenerator> reportGenerator =
        std::make_unique<ReportGenerator>(std::move(csvFormatter));

    reportGenerator->generateReport(data);

    reportGenerator->setFormatter(std::move(tabbedFormatter));
    reportGenerator->generateReport(data);

    return 0;
}
