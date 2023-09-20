#include <iostream>
#include <string>
#include <vector>

// Model (Contact Information)
class ContactModel
{
public:
    struct Contact
    {
        std::string name;
        std::string phoneNumber;
        std::string email;
    };

private:
    std::vector<Contact> contacts;

public:
    void addContact(const std::string &name, const std::string &phoneNumber, const std::string &email)
    {
        Contact contact = {name, phoneNumber, email};
        contacts.push_back(contact);
    }

    bool editContact(int index, const std::string &name, const std::string &phoneNumber, const std::string &email)
    {
        if (index >= 0 && index < contacts.size())
        {
            contacts[index].name = name;
            contacts[index].phoneNumber = phoneNumber;
            contacts[index].email = email;
            return true;
        }
        return false;
    }

    bool deleteContact(int index)
    {
        if (index >= 0 && index < contacts.size())
        {
            contacts.erase(contacts.begin() + index);
            return true;
        }
        return false;
    }

    const std::vector<Contact> &getContacts() const
    {
        return contacts;
    }
};

// View (Contact Details Display)
class ContactView
{
public:
    void displayContacts(const std::vector<ContactModel::Contact> &contacts)
    {
        std::cout << "Contact List:\n";
        for (size_t i = 0; i < contacts.size(); ++i)
        {
            std::cout << "Contact #" << i + 1 << "\n";
            std::cout << "Name: " << contacts[i].name << "\n";
            std::cout << "Phone: " << contacts[i].phoneNumber << "\n";
            std::cout << "Email: " << contacts[i].email << "\n\n";
        }
    }
};

// Controller (Contact Management)
class ContactController
{
private:
    ContactModel model;
    ContactView view;

public:
    void addContact(const std::string &name, const std::string &phoneNumber, const std::string &email)
    {
        model.addContact(name, phoneNumber, email);
    }

    bool editContact(int index, const std::string &name, const std::string &phoneNumber, const std::string &email)
    {
        return model.editContact(index, name, phoneNumber, email);
    }

    bool deleteContact(int index)
    {
        return model.deleteContact(index);
    }

    void displayContacts()
    {
        view.displayContacts(model.getContacts());
    }
};

int main()
{
    ContactController controller;

    controller.addContact("John Doe", "123-456-7890", "john@example.com");
    controller.addContact("Alice Smith", "987-654-3210", "alice@example.com");

    controller.displayContacts();

    std::cout << "\nEditing contact #1...\n";
    controller.editContact(0, "John Doe Jr.", "555-555-5555", "johndoe@example.com");

    std::cout << "\nDeleting contact #2...\n";
    controller.deleteContact(1);

    controller.displayContacts();

    return 0;
}
