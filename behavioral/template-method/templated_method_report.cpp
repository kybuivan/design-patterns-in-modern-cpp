#include <iostream>
#include <string>

// Abstract base class defining the template method
class ReportTemplate
{
public:
    // The template method that defines the report generation process
    void generateReport()
    {
        writeHeader();
        writeContent();
        writeFooter();
    }

protected:
    // Abstract methods to be implemented by subclasses
    virtual void writeHeader() = 0;
    virtual void writeContent() = 0;
    virtual void writeFooter() = 0;
};

// Concrete subclass for generating HTML reports
class HtmlReport : public ReportTemplate
{
protected:
    void writeHeader() override
    {
        std::cout << "<html><head><title>HTML Report</title></head><body>" << std::endl;
    }

    void writeContent() override
    {
        std::cout << "<h1>Report Content (HTML)</h1><p>This is the content of the HTML report.</p>" << std::endl;
    }

    void writeFooter() override
    {
        std::cout << "</body></html>" << std::endl;
    }
};

// Concrete subclass for generating PDF reports
class PdfReport : public ReportTemplate
{
protected:
    void writeHeader() override
    {
        std::cout << "PDF Report Header" << std::endl;
    }

    void writeContent() override
    {
        std::cout << "PDF Report Content" << std::endl;
    }

    void writeFooter() override
    {
        std::cout << "PDF Report Footer" << std::endl;
    }
};

int main()
{
    // Create an HTML report and generate it
    HtmlReport htmlReport;
    std::cout << "Generating HTML Report:" << std::endl;
    htmlReport.generateReport();
    std::cout << std::endl;

    // Create a PDF report and generate it
    PdfReport pdfReport;
    std::cout << "Generating PDF Report:" << std::endl;
    pdfReport.generateReport();

    return 0;
}
