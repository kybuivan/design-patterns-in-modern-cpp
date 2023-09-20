#include <iostream>
#include <string>
#include <vector>

// Model (Shopping Cart)
class ShoppingCartModel
{
private:
    std::vector<std::pair<std::string, double>> items; // std::pair: <product name, price>
public:
    void addItem(const std::string &productName, double price)
    {
        items.push_back(std::make_pair(productName, price));
    }

    void removeItem(int index)
    {
        if (index >= 0 && index < items.size())
        {
            items.erase(items.begin() + index);
        }
    }

    double calculateTotal() const
    {
        double total = 0.0;
        for (const auto &item : items)
        {
            total += item.second;
        }
        return total;
    }

    const std::vector<std::pair<std::string, double>> &getItems() const
    {
        return items;
    }
};

// View (Shopping Cart Display)
class ShoppingCartView
{
public:
    void displayCart(const ShoppingCartModel &cart)
    {
        std::cout << "Shopping Cart Contents:\n";
        const std::vector<std::pair<std::string, double>> &items = cart.getItems();
        for (size_t i = 0; i < items.size(); ++i)
        {
            std::cout << i + 1 << ". " << items[i].first << " - $" << items[i].second << std::endl;
        }
        std::cout << "Total: $" << cart.calculateTotal() << std::endl;
    }
};

// Controller (Shopping Cart Management)
class ShoppingCartController
{
private:
    ShoppingCartModel cart;
    ShoppingCartView view;

public:
    void addItemToCart(const std::string &productName, double price)
    {
        cart.addItem(productName, price);
    }

    void removeItemFromCart(int index)
    {
        cart.removeItem(index);
    }

    void displayCart()
    {
        view.displayCart(cart);
    }
};

int main()
{
    ShoppingCartController controller;

    controller.addItemToCart("Product A", 10.99);
    controller.addItemToCart("Product B", 5.99);
    controller.addItemToCart("Product C", 15.99);

    controller.displayCart();

    std::cout << "\nRemoving item 2...\n";
    controller.removeItemFromCart(1);

    controller.displayCart();

    return 0;
}
