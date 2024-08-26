#ifndef __ORDER_H__
#define __ORDER_H__

#include "cart.h"
#include "productmanager.h"

using namespace std;

class Order {
public:
    Order(int clientId, const Cart& cart);
    void process(ProductManager& productManager);
    int getOrderId() const;
    int getClientId() const;
    int getTotalAmount() const;

private:
    static int nextOrderId;
    int orderId;
    int clientId;
    map<int, pair<Product*, int> > items;
    int totalAmount;
};

#endif // __ORDER_H__
