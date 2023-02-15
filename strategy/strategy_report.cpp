#include <iostream>
#include <vector>
#include <sstream>

// Strategy interface
class ReportFormatter {
public:
    virtual std::string formatReport(const std::vector<int>& data) const = 0;
    virtual ~ReportFormatter() {}
};

// Concrete strategy classes
class CsvReportFormatter : public ReportFormatter {
public:
    std::string formatReport(const std::vector<int>& data) const override {
        std::stringstream ss;
        for (auto d : data) {
            ss << d << ",";
        }
        return ss.str();
    }
};

class TabbedReportFormatter : public ReportFormatter {
public:
    std::string formatReport(const std::vector<int>& data) const override {
        std::stringstream ss;
        for (auto d : data) {
            ss << d << "\t";
        }
        return ss.str();
    }
};

// Context class
class ReportGenerator {
private:
    ReportFormatter* formatter;

public:
    ReportGenerator(ReportFormatter* formatter) : formatter(formatter) {}

    void setFormatter(ReportFormatter* formatter) {
        this->formatter = formatter;
    }

    void generateReport(const std::vector<int>& data) {
        std::string formattedData = formatter->formatReport(data);
        std::cout << "Generated report: " << formattedData << std::endl;
    }
};

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};

    CsvReportFormatter csvFormatter;
    TabbedReportFormatter tabbedFormatter;

    ReportGenerator reportGenerator(&csvFormatter);

    reportGenerator.generateReport(data);

    reportGenerator.setFormatter(&tabbedFormatter);
    reportGenerator.generateReport(data);

    return 0;
}
