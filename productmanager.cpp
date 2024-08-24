#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "product.h"
#include "productmanager.h"

using namespace std;

ProductManager::ProductManager()
{
    ifstream file;
    file.open("productlist.txt");
    if(!file.fail()) {
        while(!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if(row.size()) {
                int id = atoi(row[0].c_str());
                Product* p = new Product(id, row[1], row[2], atoi(row[3].c_str()), atoi(row[4].c_str()));
                productList.insert({id, p});
            }
        }
    }
    file.close();
}

ProductManager::~ProductManager()
{
    ofstream file;
    file.open("productlist.txt");
    if(!file.fail()) {
        for (const auto& v : productList) {
            Product* p = v.second;
            file << p->id() << ", " << p->getName() << ", " << p->getCategory() << ", " << p->getPrice() << ", " << p->getQuantity() << endl;
        }
    }
    file.close();
}

void ProductManager::inputProduct()
{
    string name, category;
    int price, quantity;
    cout << "name : "; cin >> name;
    cout << "category : "; cin >> category;
    cout << "price : "; cin >> price;
    cout << "quantity : "; cin >> quantity;

    int id = makeId();
    Product* p = new Product(id, name, category, price, quantity);
    productList.insert({id, p});
}

Product* ProductManager::search(int id)
{
    return productList[id];
}

void ProductManager::deleteProduct(int id)
{
    productList.erase(id);
}

void ProductManager::modifyProduct(int id)
{
    Product* p = search(id);
    cout << "  ID  |     Name     | Category | Price | Quantity" << endl;
    cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getName() << " | ";
    cout << setw(12) << p->getCategory() << " | ";
    cout << setw(5) << p->getPrice() << " | ";
    cout << setw(5) << p->getQuantity() << endl;

    string name, category;
    int price, quantity;
    cout << "name : "; cin >> name;
    cout << "category : "; cin >> category;
    cout << "price : "; cin >> price;
    cout << "quantity : "; cin >> quantity;

    p->setName(name);
    p->setCategory(category);
    p->setPrice(price);
    p->setQuantity(quantity);
}

void ProductManager::displayProducts()
{
    cout << endl << "  ID  |     Name     | Category | Price | Quantity" << endl;
    for (const auto& v : productList) {
        Product* p = v.second;
        cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getName() << " | ";
        cout << setw(12) << p->getCategory() << " | ";
        cout << setw(5) << p->getPrice() << " | ";
        cout << setw(5) << p->getQuantity() << endl;
    }
}

void ProductManager::getProductByCategory(string category)
{
    cout << endl << "  ID  |     Name     | Category | Price | Quantity" << endl;
    for (const auto& v : productList) {
        Product* p = v.second;
        if (p->getCategory() == category) {
            cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
            cout << setw(12) << setfill(' ') << p->getName() << " | ";
            cout << setw(12) << p->getCategory() << " | ";
            cout << setw(5) << p->getPrice() << " | ";
            cout << setw(5) << p->getQuantity() << endl;
        }
    }
}

void ProductManager::getProductByPrice(int price)
{
    cout << endl << "  ID  |     Name     | Category | Price | Quantity" << endl;
    for (const auto& v : productList) {
        Product* p = v.second;
        if (p->getPrice() == price) {
            cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
            cout << setw(12) << setfill(' ') << p->getName() << " | ";
            cout << setw(12) << p->getCategory() << " | ";
            cout << setw(5) << p->getPrice() << " | ";
            cout << setw(5) << p->getQuantity() << endl;
        }
    }
}

void ProductManager::updateProductQuantity(int id, int quantity)
{
    Product* p = search(id);
    p->setQuantity(quantity);
}

bool ProductManager::checkProductAvailability(int id)
{
    Product* p = search(id);
    return p->getQuantity() > 0;
}

int ProductManager::makeId()
{
    if (productList.size() == 0) {
        return 0;
    } else {
        auto elem = productList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

vector<string> ProductManager::parseCSV(istream& file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            if (file.peek() == '\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c!= delimiter) break;
        } else {
            ss << c;
        }
    }
    return row;
}

bool ProductManager::displayMenu()
{
    int ch, key;
    string category;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Product Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                     " << endl;
    cout << "  2. Input Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. Modify Product                           " << endl;
    cout << "  5. Search Product by Category               " << endl;
    cout << "  6. Search Product by Price                  " << endl;
    cout << "  7. Update Product Quantity                  " << endl;
    cout << "  8. Check Product Availability               " << endl;
    cout << "  9. Quit this Program                        " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    cin >> ch;
    switch (ch) {
        case 1:
            displayProducts();
            cin.ignore();
            getchar();
            break;
        case 2:
            inputProduct();
            break;
        case 3:
            displayProducts();
            cout << "   Choose Key : ";
            cin >> key;
            deleteProduct(key);
            break;
        case 4:
            displayProducts();
            cout << "   Choose Key : ";
            cin >> key;
            modifyProduct(key);
            break;
        case 5:
            cout << "   Enter Category : ";
            cin >> category;
            getProductByCategory(category);
            cin.ignore();
            getchar();
            break;
        case 6:
            cout << "   Enter Price : ";
            int price;
            cin >> price;
            getProductByPrice(price);
            cin.ignore();
            getchar();
            break;
        case 7:
            displayProducts();
            cout << "   Choose Key : ";
            cin >> key;
            cout << "   Enter Quantity : ";
            int quantity;
            cin >> quantity;
            updateProductQuantity(key, quantity);
            break;
        case 8:
            displayProducts();
            cout << "   Choose Key : ";
            cin >> key;
            if (checkProductAvailability(key)) {
                cout << "   Product is available." << endl;
            } else {
                cout << "   Product is not available." << endl;
            }
            cin.ignore();
            getchar();
            break;
        case 9:
            return false;
        default:
            displayProducts();
            cin.ignore();
            getchar();
            break;
    }
    return true;
}