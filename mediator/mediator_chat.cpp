#include <iostream>
#include <memory>
#include <string>

class Component;

class Mediator
{
public:
    virtual ~Mediator() = default;

    virtual void notify(Component *sender, const std::string &event) = 0;
};

// Abstract Component
class Component
{
public:
    virtual ~Component() = default;

    Component(Mediator *dialog) : dialog(dialog)
    {
    }

    virtual void click()
    {
        dialog->notify(this, "click");
    }

    virtual void keypress()
    {
        dialog->notify(this, "keypress");
    }

protected:
    Mediator *dialog;
};

class Button : public Component
{
public:
    Button(Mediator *dialog) : Component(dialog)
    {
    }
};

class Textbox : public Component
{
public:
    Textbox(Mediator *dialog) : Component(dialog)
    {
    }
};

class Checkbox : public Component
{
public:
    bool checked;
    Checkbox(Mediator *dialog) : Component(dialog), checked(false)
    {
    }

    void check()
    {
        checked = !checked;
        dialog->notify(this, "check");
    }

    void keypress()
    {
    }
    void click()
    {
    }
};

class AuthenticationDialog : public Mediator
{
public:
    AuthenticationDialog()
    {
        title = "Login";
        loginOrRegisterChkBx = std::make_unique<Checkbox>(this);
        loginUsername = std::make_unique<Textbox>(this);
        loginPassword = std::make_unique<Textbox>(this);
        registrationUsername = std::make_unique<Textbox>(this);
        registrationPassword = std::make_unique<Textbox>(this);
        registrationEmail = std::make_unique<Textbox>(this);
        okBtn = std::make_unique<Button>(this);
        cancelBtn = std::make_unique<Button>(this);
    }

    void notify(Component *sender, const std::string &event) override
    {
        if (sender == loginOrRegisterChkBx.get() && event == "check")
        {
            if (loginOrRegisterChkBx->checked)
            {
                title = "Log in";
                // 1. Show login form components.
                // 2. Hide registration form components.
            }
            else
            {
                title = "Register";
                // 1. Show registration form components.
                // 2. Hide login form components.
            }
            std::cout << title << std::endl;
        }

        if (sender == okBtn.get() && event == "click")
        {
            if (loginOrRegisterChkBx->checked)
            {
                bool found = true;
                // Try to find a user using login credentials.
                if (!found)
                {
                    // Show an error message above the login field.
                }
                std::cout << "loginOrRegisterChkBx click" << std::endl;
            }
            else
            {
                // 1. Create a user account using data from the registration fields.
                // 2. Log that user in.
                // ...
            }
        }
    }

public:
    std::string title;
    std::unique_ptr<Checkbox> loginOrRegisterChkBx;
    std::unique_ptr<Textbox> loginUsername;
    std::unique_ptr<Textbox> loginPassword;
    std::unique_ptr<Textbox> registrationUsername;
    std::unique_ptr<Textbox> registrationPassword;
    std::unique_ptr<Textbox> registrationEmail;
    std::unique_ptr<Button> okBtn;
    std::unique_ptr<Button> cancelBtn;
};

int main()
{
    // Create the authentication dialog with all its components
    std::unique_ptr<AuthenticationDialog> dialog = std::make_unique<AuthenticationDialog>();

    // Simulate user interaction by clicking the checkboxes, filling
    // in fields, and clicking the buttons.
    dialog->loginOrRegisterChkBx->check();
    dialog->registrationUsername->keypress();
    dialog->registrationUsername->click();
    dialog->registrationUsername->keypress();
    dialog->registrationPassword->keypress();
    dialog->registrationPassword->click();
    dialog->registrationEmail->keypress();
    dialog->okBtn->click();
    dialog->loginUsername->keypress();
    dialog->loginUsername->click();
    dialog->loginPassword->keypress();
    dialog->loginPassword->click();
    dialog->okBtn->click();

    return 0;
}
