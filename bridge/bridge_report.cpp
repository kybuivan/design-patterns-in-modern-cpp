#include <iostream>
#include <string>

//Abstraction
class Report
{
public:
    virtual ~Report() = default;
    virtual void setFormat(const std::string &format) = 0;
    virtual std::string getReport() const = 0;
};

//Refined Abstraction
class EmployeeReport : public Report
{
public:
    explicit EmployeeReport(const std::string &employeeData) : employeeData_(employeeData)
    {
    }

    void setFormat(const std::string &format) override
    {
        format_ = format;
    }

    std::string getReport() const override
    {
        if (format_ == "pdf")
        {
            return "Employee report in PDF format: " + employeeData_;
        }
        else if (format_ == "html")
        {
            return "Employee report in HTML format: " + employeeData_;
        }
        else
        {
            return "Invalid format.";
        }
    }

private:
    std::string employeeData_;
    std::string format_;
};

//Implementor
class ReportFormat
{
public:
    virtual ~ReportFormat() = default;
    virtual std::string formatReport(const std::string &data) const = 0;
};

//Concrete Implementor
class PDFReportFormat : public ReportFormat
{
public:
    std::string formatReport(const std::string &data) const override
    {
        return "PDF format: " + data;
    }
};

//Concrete Implementor
class HTMLReportFormat : public ReportFormat
{
public:
    std::string formatReport(const std::string &data) const override
    {
        return "HTML format: " + data;
    }
};

int main()
{
    EmployeeReport report("John Doe - Manager");
    report.setFormat("pdf");
    std::cout << report.getReport() << std::endl;
    report.setFormat("html");
    std::cout << report.getReport() << std::endl;
    report.setFormat("invalid");
    std::cout << report.getReport() << std::endl;
    return 0;
}
