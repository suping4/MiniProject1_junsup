#include "cart.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 카트에 항목을 추가하는 메소드
void Cart::addItem(Product* product, int quantity) {
    // 제품 ID를 가져옴
    int productId = product->id();
    
    // 이미 카트에 해당 제품이 있는지 확인
    if (items.find(productId) != items.end()) {
        // 이미 있는 경우 수량을 증가시킴
        items[productId].second += quantity;
    } else {
        // 없는 경우 새로 추가
        items[productId] = make_pair(product, quantity);
    }
}

// 카트에서 항목을 제거하는 메소드
void Cart::removeItem(int productId) {
    // 해당 제품을 카트에서 제거
    items.erase(productId);
}

// 카트의 항목 수량을 업데이트 하는 메소드
void Cart::updateQuantity(int productId, int quantity) {
    // 해당 제품이 카트에 있는지 확인
    if (items.find(productId) != items.end()) {
        // 수량을 업데이트
        items[productId].second = quantity;
    }
}

// 카트 내용을 출력하는 메소드
void Cart::displayCart() const {
    cout << "\n장바구니 내용:\n";
    cout << setw(5) << "ID" << " | " 
         << setw(12) << "이름" << " | "
         << setw(8) << "가격" << " | "
         << setw(8) << "수량" << " | "
         << setw(10) << "총액" << endl;
    cout << string(50, '-') << endl;

    int total = 0;  // 총 금액을 계산하기 위한 변수
    for (const auto& item : items) {
        Product* product = item.second.first;  // 제품 객체를 가져옴
        int quantity = item.second.second;     // 수량을 가져옴
        int subtotal = product->getPrice() * quantity;  // 부분 금액 계산
        total += subtotal;  // 총 금액에 부분 금액을 더함

        cout << setw(5) << product->id() << " | "
             << setw(12) << product->getName() << " | "
             << setw(8) << product->getPrice() << " | "
             << setw(8) << quantity << " | "
             << setw(10) << subtotal << endl;
    }
    cout << string(50, '-') << endl;
    cout << "총 금액: " << total << endl;  // 총 금액 출력
}

// 카트를 초기화하는 메소드
void Cart::clear() {
    // 카트의 모든 항목을 제거
    items.clear();
}

// 카트가 비어 있는지 확인하는 메소드
bool Cart::isEmpty() const {
    // 카트가 비어 있는지 여부를 반환
    return items.empty();
}

// 카트의 항목을 반환하는 메소드
const map<int, pair<Product*, int>>& Cart::getItems() const {
    // 카트의 항목을 반환
    return items;
}