#ifndef __CART_H__
#define __CART_H__

#include <map>
#include "product.h"

using namespace std;

class Cart {
public:
    void addItem(Product* product, int quantity);
    void removeItem(int productId);
    void updateQuantity(int productId, int quantity);
    void displayCart() const;
    void clear();
    bool isEmpty() const;
    const map<int, pair<Product*, int> >& getItems() const;

private:
    map<int, pair<Product*, int> > items; // productId -> (Product*, quantity)
};

#endif // __CART_H__