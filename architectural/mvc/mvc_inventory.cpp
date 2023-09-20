#include <iostream>
#include <map>
#include <string>

// Model (Inventory)
class InventoryModel
{
private:
    std::map<std::string, int> products; // Product name and quantity in stock

public:
    void addProduct(const std::string &productName, int quantity)
    {
        products[productName] += quantity;
    }

    void removeProduct(const std::string &productName, int quantity)
    {
        if (products.find(productName) != products.end())
        {
            products[productName] -= quantity;
            if (products[productName] < 0)
            {
                products[productName] = 0;
            }
        }
    }

    const std::map<std::string, int> &getInventory() const
    {
        return products;
    }
};

// View (Inventory Display)
class InventoryView
{
public:
    void displayInventory(const InventoryModel &inventory)
    {
        std::cout << "Product Listing and Stock Status:\n";
        for (const auto &entry : inventory.getInventory())
        {
            std::cout << entry.first << " - Stock: " << entry.second << std::endl;
        }
    }
};

// Controller (Inventory Management)
class InventoryController
{
private:
    InventoryModel model;
    InventoryView view;

public:
    void addProductToInventory(const std::string &productName, int quantity)
    {
        model.addProduct(productName, quantity);
    }

    void removeProductFromInventory(const std::string &productName, int quantity)
    {
        model.removeProduct(productName, quantity);
    }

    void displayInventory()
    {
        view.displayInventory(model);
    }
};

int main()
{
    InventoryController controller;

    controller.addProductToInventory("Product A", 100);
    controller.addProductToInventory("Product B", 50);
    controller.addProductToInventory("Product C", 75);

    controller.displayInventory();

    std::cout << "\nRemoving 20 units of Product A...\n";
    controller.removeProductFromInventory("Product A", 20);

    controller.displayInventory();

    return 0;
}
