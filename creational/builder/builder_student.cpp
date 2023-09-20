#include <iostream>
#include <memory>
#include <string>

// Product: UserForm
class UserForm
{
public:
    void AddTextField(const std::string &label, const std::string &value)
    {
        form += label + ": " + value + "\n";
    }

    void AddButton(const std::string &label, bool isEnabled)
    {
        form += "Button: " + label + " (Enabled: " + (isEnabled ? "Yes" : "No") + ")\n";
    }

    void Display()
    {
        std::cout << "User Form:\n" << form << std::endl;
    }

private:
    std::string form;
};

// Abstract Builder: UserFormBuilder
class UserFormBuilder
{
public:
    virtual void BuildTextField(const std::string &value) = 0;
    virtual void BuildButton(bool isEnabled) = 0;
    virtual std::shared_ptr<UserForm> GetUserForm() = 0;
};

// Concrete Builder: AdminFormBuilder
class AdminFormBuilder : public UserFormBuilder
{
public:
    AdminFormBuilder()
    {
        form = std::make_shared<UserForm>();
    }

    void BuildTextField(const std::string &value) override
    {
        form->AddTextField("Admin Name", value);
    }

    void BuildButton(bool isEnabled) override
    {
        form->AddButton("Edit Grades", isEnabled);
        form->AddButton("Manage Users", isEnabled);
        form->AddButton("Logout", true);
    }

    std::shared_ptr<UserForm> GetUserForm() override
    {
        return form;
    }

private:
    std::shared_ptr<UserForm> form;
};

// Concrete Builder: StudentFormBuilder
class StudentFormBuilder : public UserFormBuilder
{
public:
    StudentFormBuilder()
    {
        form = std::make_shared<UserForm>();
    }

    void BuildTextField(const std::string &value) override
    {
        form->AddTextField("Student Name", value);
    }

    void BuildButton(bool isEnabled) override
    {
        form->AddButton("View Grades", isEnabled);
        form->AddButton("Logout", true);
    }

    std::shared_ptr<UserForm> GetUserForm() override
    {
        return form;
    }

private:
    std::shared_ptr<UserForm> form;
};

// Director: Application
class Application
{
public:
    void SetBuilder(std::shared_ptr<UserFormBuilder> builder)
    {
        this->builder = builder;
    }

    std::shared_ptr<UserForm> BuildUserForm(const std::string &username, bool isAdmin)
    {
        builder->BuildTextField(username);
        builder->BuildButton(isAdmin);
        return builder->GetUserForm();
    }

private:
    std::shared_ptr<UserFormBuilder> builder;
};

int main()
{
    Application app;

    // Create an admin form
    std::shared_ptr<UserFormBuilder> adminBuilder = std::make_shared<AdminFormBuilder>();
    app.SetBuilder(adminBuilder);
    std::shared_ptr<UserForm> adminForm = app.BuildUserForm("AdminUser", true);

    // Create a student form
    std::shared_ptr<UserFormBuilder> studentBuilder = std::make_shared<StudentFormBuilder>();
    app.SetBuilder(studentBuilder);
    std::shared_ptr<UserForm> studentForm = app.BuildUserForm("StudentUser", false);

    // Display the forms
    std::cout << "Admin Form:" << std::endl;
    adminForm->Display();
    std::cout << "\nStudent Form:" << std::endl;
    studentForm->Display();

    return 0;
}
