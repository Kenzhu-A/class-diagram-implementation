#include <iostream>
#include <cstring>
#include <cctype>
#include <vector>
#include <iomanip>

using namespace std;

class Product {
private:
    string productID;
    string name;
    double price;

public:
    Product(string pid, string pname, double pprice) : productID(pid), name(pname), price(pprice) {}

    string getProductID() const { return productID; }
    string getProductName() const { return name; }
    double getProductPrice() const { return price; }
};

bool caseInsensitiveCompare(const string& s1, const string& s2) {
    if (s1.size() != s2.size())

        return false;

    for (size_t i = 0; i < s1.size(); i++) {

        if (tolower(s1[i]) != tolower(s2[i]))
            return false;

    }

    return true;

}


class ShoppingCart {
private:
    vector<Product> cart_products;
    vector<int> cart_quantities;

public:
    void addProduct(const Product& product, int quantity) {
        cart_products.push_back(product);
        cart_quantities.push_back(quantity);
        cout << "Product added successfully!" << endl;
    }

    void viewCart() const {
        if (cart_products.empty()) {
            cout << "Your shopping cart is empty." << endl;
            return;
        }

        cout << setw(30) << left << "Product ID" << setw(30) << left << "Name" << setw(30) << left << "Price" << setw(30) << left << "Quantity" << endl;
        for (size_t i = 0; i < cart_products.size(); i++) {
            cout << setw(30) << left << cart_products[i].getProductID() << setw(30) << left << cart_products[i].getProductName()
                 << setw(30) << left << cart_products[i].getProductPrice() << setw(30) << left << cart_quantities[i] << endl;
        }
    }

    bool isEmpty() const {
        return cart_products.empty();
    }

    vector<Product> getCartProducts() const {
        return cart_products;
    }

    vector<int> getCartQuantities() const {
        return cart_quantities;
    }

    void clearCart() {
        cart_products.clear();
        cart_quantities.clear();
    }
};

class Order {
private:
    int order_id;
    vector<Product> ordered_products;
    vector<int> ordered_quantities;
    double total_amount;

public:

    Order(int oid, const ShoppingCart& cart) : order_id(oid), ordered_products(cart.getCartProducts()), ordered_quantities(cart.getCartQuantities()) {
        
        total_amount = 0;

        for (size_t i = 0; i < ordered_products.size(); i++) {
            total_amount += ordered_products[i].getProductPrice() * ordered_quantities[i];
        }
    }

    void viewOrder() const {
        cout << "\nOrder ID: " << order_id << endl;
        cout << "Total Amount: P" << total_amount << endl;
        cout << "Order Details: " << endl;
        cout << setw(30) << left << "Product ID" << setw(30) << left << "Name" << setw(30) << left << "Price" << setw(30) << left << "Quantity" << endl;
        for (size_t i = 0; i < ordered_products.size(); i++) {

            double product_total = ordered_products[i].getProductPrice() * ordered_quantities[i];

            cout << setw(30) << left << ordered_products[i].getProductID() << setw(30) << left << ordered_products[i].getProductName()
                 << setw(30) << left << ordered_products[i].getProductPrice() << setw(30) << left << ordered_quantities[i]  << endl;
        }
        
    }
};

class StoreManager {
    
    private:

    vector<Product> productList;
    ShoppingCart cart;
    vector<Order> orders;
    int orderCounter = 1;

    public:
   
     StoreManager() {

        productList = {

            Product("ABC", "Coke Mismo", 25.00),
            Product("DEF", "Dairy Milk Chocolate", 16.00),
            Product("GHI", "Pancit Canton", 28.00),
            Product("JKL", "Piattos Chips", 23.00),
            Product("MNO", "Water Bottle", 17.00)

        };
    }

    void displayProducts() {

        string productID;
        int quantity;
        char another = 'Y';

        while (another == 'Y' || another == 'y') {

            cout << setw(30) << left << "Product ID" << setw(30) << left << "Name" << setw(30) << left << "Price" << endl;
        
        for (const auto& product : productList) {

            cout << setw(30) << left << product.getProductID() << setw(30) << left << product.getProductName() << setw(30) << left << product.getProductPrice() << endl;
        
        }

            cout << "\nEnter the Product ID to add to the cart: ";
            cin >> productID;

            Product* selected_product = nullptr;

            for (auto& product : productList) {

                if (caseInsensitiveCompare(product.getProductID(), productID)) {

                    selected_product = &product;
                    break;
                }

            }

            if (selected_product) {

                cout << "Enter the quantity: ";
             
                cin >> quantity;

                cart.addProduct(*selected_product, quantity);

            } 
            
            else {
                cout << "Invalid Product ID." << endl;
            }

            cout << "Do you want to add another product? (Y/N): ";
            cin >> another;

        }
    }

    void displayShoppingCart() {

        char checkout;

        cart.viewCart();

        if (!cart.isEmpty()) {

            
            cout << "\nDo you want to check out all the products? (Y/N): ";
            cin >> checkout;

            if (checkout == 'Y' || checkout == 'y') {

                Order new_order(orderCounter++, cart);

                orders.push_back(new_order);

                new_order.viewOrder();
                
                cout << "\nYou have successfully checked out the products!" << endl;

                cart.clearCart();
            }
        }
    }

    void displayOrders() const {
        if (orders.empty()) {

            cout << "No orders to display." << endl;

        } else {
            for (const auto& order : orders) {
                order.viewOrder();
            }
        }
    }
};

void displayMenu() {
    cout << "================MENU================\n";
    cout << "1. View Products\n";
    cout << "2. View Shopping Cart\n";
    cout << "3. View Orders\n";
    cout << "4. Exit\n";
    cout << "====================================\n";
}

int main() {
    StoreManager manager;
    int choice = 0;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:

            manager.displayProducts();
            break;

        case 2:

            manager.displayShoppingCart();
            break;

        case 3:

            manager.displayOrders();
            break;

        case 4:

            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Input! Please enter a choice between 1-4.\n";

        }
    } while (choice != 4);

    return 0;
}
