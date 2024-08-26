#include "cart.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Cart::addItem(Product* product, int quantity) {
    int productId = product->id();
    if (items.find(productId) != items.end()) {
        items[productId].second += quantity;
    } else {
        items[productId] = make_pair(product, quantity);
    }
}

void Cart::removeItem(int productId) {
    items.erase(productId);
}

void Cart::updateQuantity(int productId, int quantity) {
    if (items.find(productId) != items.end()) {
        items[productId].second = quantity;
    }
}

void Cart::displayCart() const {
    cout << "\n장바구니 내용:\n";
    cout << setw(5) << "ID" << " | " 
         << setw(12) << "이름" << " | "
         << setw(8) << "가격" << " | "
         << setw(8) << "수량" << " | "
         << setw(10) << "총액" << endl;
    cout << string(50, '-') << endl;

    int total = 0;
    for (const auto& item : items) {
        Product* product = item.second.first;
        int quantity = item.second.second;
        int subtotal = product->getPrice() * quantity;
        total += subtotal;

        cout << setw(5) << product->id() << " | "
             << setw(12) << product->getName() << " | "
             << setw(8) << product->getPrice() << " | "
             << setw(8) << quantity << " | "
             << setw(10) << subtotal << endl;
    }
    cout << string(50, '-') << endl;
    cout << "총 금액: " << total << endl;
}

void Cart::clear() {
    items.clear();
}

bool Cart::isEmpty() const {
    return items.empty();
}

const map<int, pair<Product*, int>>& Cart::getItems() const {
    return items;
}