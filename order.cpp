#include "order.h"
#include <iostream>

using namespace std;

int Order::nextOrderId = 1;

Order::Order(int clientId, const Cart& cart) 
    : orderId(nextOrderId++), clientId(clientId), items(cart.getItems()), totalAmount(0) {
    for (const auto& item : items) {
        totalAmount += item.second.first->getPrice() * item.second.second;
    }
}

void Order::process(ProductManager& productManager) {
    cout << "주문 처리 중...\n";
    for (const auto& item : items) {
        Product* product = item.second.first;
        int quantity = item.second.second;
        
        if (productManager.checkProductAvailability(product->id())) {
            int currentQuantity = product->getQuantity();
            if (currentQuantity >= quantity) {
                productManager.updateProductQuantity(product->id(), currentQuantity - quantity);
                cout << product->getName() << " " << quantity << "개 주문 완료\n";
            } else {
                cout << product->getName() << " 재고 부족. 주문 실패\n";
                totalAmount -= product->getPrice() * quantity;
            }
        } else {
            cout << product->getName() << " 제품 없음. 주문 실패\n";
            totalAmount -= product->getPrice() * quantity;
        }
    }
    cout << "주문 번호: " << orderId << "\n";
    cout << "총 주문 금액: " << totalAmount << "\n";
}

int Order::getOrderId() const {
    return orderId;
}

int Order::getClientId() const {
    return clientId;
}

int Order::getTotalAmount() const {
    return totalAmount;
}
