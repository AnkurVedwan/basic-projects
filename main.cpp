#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class temp {
    string itemID, itemName;
    int itemQuantity, itemPrice;
    fstream file, file1;
    string search;
    char choice1;
    int totalamount, quantity, itemrate;

public:
    void addproduct();
    void viewproduct();
    void buyproduct();
} obj;

int main() {
    char choice;
    cout << "Press 1 --> Start Shopping" << endl;
    cout << "Press 0 --> Exit" << endl;
    cin >> choice;

    switch (choice) {
    case 'A':
        obj.addproduct();
        break;
    case '1':
        obj.viewproduct();
        obj.buyproduct();
        break;
    case '0':
        cout << "Exiting program..." << endl;
        exit(0);
        break;
    default:
        cout << "Invalid selection....!" << endl;
        break;
    }
    return 0;
}

void temp::addproduct() {
    int x;
    cout << "Enter The Number of Products to Add : ";
    cin >> x;
    for(int i=0;i<x;i++)
    {
    cout << "Enter Product ID: ";
    cin >> itemID;
    cout << "Enter Product Name: ";
    cin >> itemName;
    cout << "Enter Product Quantity: ";
    cin >> itemQuantity;
    cout << "Enter Product Price: ";
    cin >> itemPrice;

    file.open("data.txt", ios::out | ios::app);
    file << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
    file.close();
    cout << "Product added successfully!" << endl;
    }
}

void temp::viewproduct() {
    file.open("data.txt", ios::in);
    cout << "---------------------------" << endl;
    cout << "Product ID\tProduct Name\tQuantity\tProduct Price" << endl;

    while (file >> itemID >> itemName >> itemQuantity >> itemPrice) {
        cout << itemID << "\t\t" << itemName << "\t\t" << itemQuantity << "\t\t" << itemPrice << endl;
    }
    cout << "---------------------------" << endl;
    file.close();
}

void temp::buyproduct() {
    choice1 = 'y';
    totalamount = 0;
    while (choice1 == 'y') {
        file.open("data.txt", ios::in);
        file1.open("temp.txt", ios::out);

        cout << "Enter Product ID: ";
        cin >> search;
        cout << "Enter Quantity: ";
        cin >> quantity;

        bool found = false;
        while (file >> itemID >> itemName >> itemQuantity >> itemPrice) {
            if (itemID == search) {
                found = true;
                if (itemQuantity >= quantity) {
                    itemQuantity -= quantity;
                    itemrate = quantity * itemPrice;
                    totalamount += itemrate;

                    cout << "-------Payment Bill---------\n";
                    cout << "Product ID: " << itemID << "\n";
                    cout << "Product Name: " << itemName << "\n";
                    cout << "Quantity: " << quantity << "\n";
                    cout << "Item Rate: " << itemrate << "\n";
                    cout << "Total Amount Purchased: " << totalamount << "\n";
                    cout << "----------------------------\n";
                } else {
                    cout << "Insufficient stock for product ID: " << itemID << endl;
                }
            }
            file1 << itemID << "\t" << itemName << "\t" << itemQuantity << "\t" << itemPrice << endl;
        }

        if (!found) {
            cout << "Product ID not found!" << endl;
        }

        file.close();
        file1.close();

        remove("data.txt");
        rename("temp.txt", "data.txt");

        cout << "Continue Shopping? (y/n): ";
        cin >> choice1;
    }
}
