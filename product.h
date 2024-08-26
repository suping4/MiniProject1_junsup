#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <iostream>

using namespace std;
zcc
class Product {
public:
    Product(int id = 0, string name = "", string category = "", int price = 0, int quantity = 0);

    string getName() const;
    void setName(string&);
    string getCategory() const;
    void setCategory(string&);
    int getPrice() const;
    void setPrice(int);
    int getQuantity() const;
    void setQuantity(int);
    int id() const;
    bool operator==(const Product &other) const;

private:
    int m_id;
    string m_name;
    string m_category;
    int m_price;
    int m_quantity;
};
#endif          // __PRODUCT_H__