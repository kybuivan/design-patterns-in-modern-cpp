#include <iostream>
#include <memory>
#include <string>

// Abstract Prototype: DataObject
class DataObject
{
public:
    virtual std::shared_ptr<DataObject> Clone() = 0;
    virtual void Process() = 0;
};

// Concrete Prototype: SalesDataObject
class SalesDataObject : public DataObject
{
public:
    SalesDataObject(const std::string &data) : data(data)
    {
    }

    std::shared_ptr<DataObject> Clone() override
    {
        return std::make_shared<SalesDataObject>(*this);
    }

    void Process() override
    {
        // Simulate data analysis on sales data
        std::cout << "Processing Sales Data: " << data << std::endl;
        // Perform analysis logic here...
    }

private:
    std::string data;
};

// Client: DataAnalyzer
class DataAnalyzer
{
public:
    DataAnalyzer(std::shared_ptr<DataObject> dataObject) : dataObject(dataObject)
    {
    }

    void AnalyzeData()
    {
        // Process and analyze data
        dataObject->Process();
    }

    void SetDataObject(std::shared_ptr<DataObject> newDataObject)
    {
        dataObject = newDataObject;
    }

private:
    std::shared_ptr<DataObject> dataObject;
};

int main()
{
    // Create a SalesDataObject from database query
    std::shared_ptr<DataObject> salesData = std::make_shared<SalesDataObject>("SalesDataFromDB");

    // Perform the first analysis
    DataAnalyzer analyzer1(salesData);
    analyzer1.AnalyzeData();

    // Clone the data object for a second analysis
    std::shared_ptr<DataObject> clonedData = salesData->Clone();

    // Perform the second analysis with the cloned data
    DataAnalyzer analyzer2(clonedData);
    analyzer2.AnalyzeData();

    return 0;
}
