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
    cout << "품명 : "; cin >> name;
    cout << "카테고리 : "; cin >> category;
    cout << "가격 : "; cin >> price;
    cout << "수량 : "; cin >> quantity;

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
    cout << "  ID  |     품명     |   카테고리   |  가격 |  수량" << endl;
    cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getName() << " | ";
    cout << setw(12) << p->getCategory() << " | ";
    cout << setw(5) << p->getPrice() << " | ";
    cout << setw(5) << p->getQuantity() << endl;

    string name, category;
    int price, quantity;
    cout << "품명 : "; cin >> name;
    cout << "카테고리 : "; cin >> category;
    cout << "가격 : "; cin >> price;
    cout << "수량 : "; cin >> quantity;

    p->setName(name);
    p->setCategory(category);
    p->setPrice(price);
    p->setQuantity(quantity);
}

void ProductManager::displayProducts()
{
    cout << endl << "  ID  |     품명     |   카테고리   |  가격 |  수량" << endl;
    for (const auto& v : productList) {
        Product* p = v.second;
        cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getName() << " | ";
        cout << setw(12) << p->getCategory() << " | ";
        cout << setw(5) << p->getPrice() << " | ";
        cout << setw(5) << p->getQuantity() << endl;
    }
}

void ProductManager::getProductByCategory(string category) {
    cout << endl << "  ID  |     품명     |   카테고리   |  가격 |  수량" << endl;
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

void ProductManager::getProductByPrice(int price) {
    cout << endl << "  ID  |     품명     |   카테고리   |  가격 |  수량" << endl;
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

void ProductManager::updateProductQuantity(int id, int quantity) {
    Product* p = search(id);
    if (p != nullptr) {
        p->setQuantity(quantity);
        cout << "제품 수량이 업데이트되었습니다." << endl;
    } else {
        cout << "해당 ID의 제품을 찾을 수 없습니다." << endl;
    }
}

bool ProductManager::checkProductAvailability(int id) {
    Product* p = search(id);
    if (p != nullptr) {
        return p->getQuantity() > 0;
    }
    return false;
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