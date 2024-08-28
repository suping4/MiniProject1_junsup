#include "order.h"
#include <iostream>

using namespace std;

// 주문 번호를 자동으로 증가시키기 위한 정적 변수
int Order::nextOrderId = 1;

// Order 클래스의 생성자
Order::Order(int clientId, const Cart& cart) 
    : orderId(nextOrderId++),  // 다음 주문 번호를 할당하고 증가시킴
      clientId(clientId),      // 클라이언트 ID를 할당
      items(cart.getItems()),  // 카트의 항목을 할당
      totalAmount(0) {         // 총 주문 금액을 초기화
    // 총 주문 금액 계산
    for (const auto& item : items) {
        totalAmount += item.second.first->getPrice() * item.second.second;
    }
}

// 주문 처리 메소드
void Order::process(ProductManager& productManager) {
    cout << "주문 처리 중...\n";
    // 카트의 각 항목을 처리
    for (const auto& item : items) {
        Product* product = item.second.first;  // 제품 객체를 가져옴
        int quantity = item.second.second;     // 주문 수량을 가져옴
        
        // 제품이 존재하는지 확인
        if (productManager.checkProductAvailability(product->id())) {
            int currentQuantity = product->getQuantity();  // 현재 재고 수량을 가져옴
            if (currentQuantity >= quantity) {  // 재고 수량이 충분한지 확인
                productManager.updateProductQuantity(product->id(), currentQuantity - quantity);
                cout << product->getName() << " " << quantity << "개 주문 완료\n";
            } else {
                cout << product->getName() << " 재고 부족. 주문 실패\n";
                totalAmount -= product->getPrice() * quantity;  // 총 금액에서 해당 제품 금액을 차감
            }
        } else {
            cout << product->getName() << " 제품 없음. 주문 실패\n";
            totalAmount -= product->getPrice() * quantity;  // 총 금액에서 해당 제품 금액을 차감
        }
    }
    cout << "주문 번호: " << orderId << "\n";  // 주문 번호 출력
    cout << "총 주문 금액: " << totalAmount << "\n";  // 총 주문 금액 출력
}

// 주문 번호를 반환하는 메소드
int Order::getOrderId() const {
    return orderId;  // 주문 번호를 반환
}

// 클라이언트 ID를 반환하는 메소드
int Order::getClientId() const {
    return clientId;  // 클라이언트 ID를 반환
}

// 총 주문 금액을 반환하는 메소드
int Order::getTotalAmount() const {
    return totalAmount;  // 총 주문 금액을 반환
}