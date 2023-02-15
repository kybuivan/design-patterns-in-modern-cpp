#include <iostream>
#include <string>
#include <vector>
class Component;

class Mediator
{
  public:
    virtual void notify(Component *sender, const std::string &event) = 0;
};

// Abstract Component
class Component {
public:
    virtual ~Component() {}

    Component(Mediator* dialog) : dialog(dialog) {}

    virtual void click() {
        dialog->notify(this, "click");
    }

    virtual void keypress() {
        dialog->notify(this, "keypress");
    }

protected:
    Mediator* dialog;
};

class Button : public Component
{
  public:
    Button(Mediator *dialog) : Component(dialog) {}
};

class Textbox : public Component
{
  public:
    Textbox(Mediator *dialog) : Component(dialog) {}
};

class Checkbox : public Component
{
  public:
  	bool checked;
    Checkbox(Mediator *dialog) : Component(dialog), checked (false) {}

    void check()
    {
		checked = !checked;
        dialog->notify(this, "check");
    }
    void keypress(){};
    void click(){};
};

class AuthenticationDialog : public Mediator
{
  public:
    AuthenticationDialog()
    {
        title = "Login";
        loginOrRegisterChkBx = new Checkbox(this);
        loginUsername = new Textbox(this);
        loginPassword = new Textbox(this);
        registrationUsername = new Textbox(this);
        registrationPassword = new Textbox(this);
        registrationEmail = new Textbox(this);
        okBtn = new Button(this);
        cancelBtn = new Button(this);
    }

    void notify(Component *sender, const std::string &event) override
    {
        if (sender == loginOrRegisterChkBx && event == "check")
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
                // 2. Hide login form components
            }
			std::cout << title << std::endl;
        }

        if (sender == okBtn && event == "click")
        {
            if (loginOrRegisterChkBx->checked)
            {
				bool found;
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
    Checkbox *loginOrRegisterChkBx;
    Textbox *loginUsername;
    Textbox *loginPassword;
    Textbox *registrationUsername;
    Textbox *registrationPassword;
    Textbox *registrationEmail;
    Button *okBtn;
    Button *cancelBtn;
};

int main(int argc, char** argv) {
    // Create the authentication dialog with all its components
    AuthenticationDialog* dialog = new AuthenticationDialog();

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

    // Clean up the memory allocated for the dialog and all its components
    delete dialog;

    return 0;
}