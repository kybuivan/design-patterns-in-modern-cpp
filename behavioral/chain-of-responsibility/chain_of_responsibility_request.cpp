#include <iostream>
#include <memory>

// Abstract Handler: PurchaseApprover
class PurchaseApprover
{
public:
    virtual void ProcessRequest(double purchaseAmount) = 0;
    virtual void SetNextApprover(std::shared_ptr<PurchaseApprover> nextApprover) = 0;
};

// Concrete Handler: DepartmentHead
class DepartmentHead : public PurchaseApprover
{
public:
    DepartmentHead(std::string name, double approvalLimit) : name(name), approvalLimit(approvalLimit), nextApprover(nullptr)
    {
    }

    void ProcessRequest(double purchaseAmount) override
    {
        if (purchaseAmount <= approvalLimit)
        {
            std::cout << "Department Head (" << name << ") approved the purchase." << std::endl;
        }
        else if (nextApprover != nullptr)
        {
            nextApprover->ProcessRequest(purchaseAmount);
        }
        else
        {
            std::cout << "Purchase request denied." << std::endl;
        }
    }

    void SetNextApprover(std::shared_ptr<PurchaseApprover> next) override
    {
        nextApprover = next;
    }

private:
    std::string name;
    double approvalLimit;
    std::shared_ptr<PurchaseApprover> nextApprover;
};

// Concrete Handler: MaterialsDepartment
class MaterialsDepartment : public PurchaseApprover
{
public:
    MaterialsDepartment(std::string name, double approvalLimit) : name(name), approvalLimit(approvalLimit), nextApprover(nullptr)
    {
    }

    void ProcessRequest(double purchaseAmount) override
    {
        if (purchaseAmount <= approvalLimit)
        {
            std::cout << "Materials Department (" << name << ") approved the purchase." << std::endl;
        }
        else if (nextApprover != nullptr)
        {
            nextApprover->ProcessRequest(purchaseAmount);
        }
        else
        {
            std::cout << "Purchase request denied." << std::endl;
        }
    }

    void SetNextApprover(std::shared_ptr<PurchaseApprover> next) override
    {
        nextApprover = next;
    }

private:
    std::string name;
    double approvalLimit;
    std::shared_ptr<PurchaseApprover> nextApprover;
};

// Client: PurchaseRequest
class PurchaseRequest
{
public:
    PurchaseRequest(double amount) : amount(amount)
    {
    }

    void Process(std::shared_ptr<PurchaseApprover> approver)
    {
        approver->ProcessRequest(amount);
    }

private:
    double amount;
};

int main()
{
    // Create a chain of approvers
    std::shared_ptr<PurchaseApprover> departmentHead = std::make_shared<DepartmentHead>("Department Head", 1000.0);
    std::shared_ptr<PurchaseApprover> materialsDepartment = std::make_shared<MaterialsDepartment>("Materials Dept.", 5000.0);

    // Set up the chain
    departmentHead->SetNextApprover(materialsDepartment);

    // Create a purchase request
    PurchaseRequest request1(800.0);
    PurchaseRequest request2(3500.0);
    PurchaseRequest request3(7000.0);

    // Process the purchase requests
    request1.Process(departmentHead);
    request2.Process(departmentHead);
    request3.Process(departmentHead);

    return 0;
}
