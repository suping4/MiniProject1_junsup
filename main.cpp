#include <iostream>
#include <string>
#include "client.h"
#include "product.h"
#include "clientmanager.h"
#include "productmanager.h"
#include "cart.h"
#include "order.h"

using namespace std;

void displayMainMenu() {
    cout << "\n*********  쇼핑몰 프로그램  *********" << endl;
    cout << "  1. 쇼핑몰" << endl;
    cout << "  2. 고객 관리" << endl;
    cout << "  3. 제품 관리" << endl;
    cout << "  4. 프로그램 종료" << endl;
    cout << "************************************" << endl;
    cout << "메뉴를 선택하세요: ";
}

void displayShoppingMenu() {
    cout << "\n**********    쇼핑몰    **********" << endl;
    cout << "  1. 제품 목록 보기" << endl;
    cout << "  2. 장바구니에 제품 추가" << endl;
    cout << "  3. 장바구니 보기" << endl;
    cout << "  4. 주문하기" << endl;
    cout << "  5. 로그아웃" << endl;
    cout << "************************************" << endl;
    cout << "메뉴를 선택하세요: ";
}

void displayClientMenu() {
    cout << "\n**********    고객 관리    **********" << endl;
    cout << "  1. 고객 목록 보기" << endl;
    cout << "  2. 고객 추가" << endl;
    cout << "  3. 고객 정보 수정" << endl;
    cout << "  4. 고객 삭제" << endl;
    cout << "  5. 메인 메뉴로 돌아가기" << endl;
    cout << "************************************" << endl;
    cout << "메뉴를 선택하세요: ";
}

void displayProductMenu() {
    cout << "\n**********    제품 관리    **********" << endl;
    cout << "  1. 제품 목록 보기" << endl;
    cout << "  2. 제품 추가" << endl;
    cout << "  3. 제품 삭제" << endl;
    cout << "  4. 제품 정보 수정" << endl;
    cout << "  5. 카테고리별 제품 검색" << endl;
    cout << "  6. 가격별 제품 검색" << endl;
    cout << "  7. 제품 수량 업데이트" << endl;
    cout << "  8. 제품 재고 확인" << endl;
    cout << "  9. 메인 메뉴로 돌아가기" << endl;
    cout << "************************************" << endl;
    cout << "원하는 작업을 선택하세요: ";
}

Client* login(ClientManager& clientManager) {
    string name, phoneNumber;
    cout << "이름: ";
    cin >> name;
    cout << "전화번호: ";
    cin >> phoneNumber;
    
    Client* client = clientManager.login(name, phoneNumber);
    if (client) {
        cout << "로그인 성공! 환영합니다, " << client->getName() << "님." << endl;
    } else {
        cout << "로그인 실패. 이름과 전화번호를 확인해주세요." << endl;
    }
    return client;
}

void handleShopping(ClientManager& clientManager, ProductManager& productManager) {
    Client* currentClient = nullptr;
    Cart cart;
    int choice;

    while (true) {
        if (!currentClient) {
            cout << "\n1. 로그인" << endl;
            cout << "2. 회원가입" << endl;
            cout << "3. 메인 메뉴로 돌아가기" << endl;
            cout << "메뉴를 선택하세요: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    currentClient = login(clientManager);
                    if (!currentClient) continue;
                    break;
                case 2:
                    cout << "\n회원가입을 시작합니다." << endl;
                    clientManager.inputClient();
                    cout << "회원가입이 완료되었습니다. 로그인해주세요." << endl;
                    continue;
                case 3:
                    return;
                default:
                    cout << "잘못된 선택입니다." << endl;
                    continue;
            }
        }

        displayShoppingMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                productManager.displayProducts();
                break;
            case 2: {
                int productId, quantity;
                cout << "제품 ID: ";
                cin >> productId;
                cout << "수량: ";
                cin >> quantity;
                Product* product = productManager.search(productId);
                if (product && productManager.checkProductAvailability(productId)) {
                    cart.addItem(product, quantity);
                    cout << "제품이 장바구니에 추가되었습니다." << endl;
                } else {
                    cout << "제품이 존재하지 않거나 재고가 부족합니다." << endl;
                }
                break;
            }
            case 3:
                cart.displayCart();
                break;
            case 4:
                if (cart.isEmpty()) {
                    cout << "장바구니가 비어있습니다." << endl;
                } else {
                    Order order(currentClient->id(), cart);
                    order.process(productManager);
                    cart.clear();
                }
                break;
            case 5:
                cout << "로그아웃 되었습니다." << endl;
                currentClient = nullptr;
                cart.clear();
                break;
            default:
                cout << "잘못된 선택입니다." << endl;
        }
    }
}

void handleClientManagement(ClientManager& clientManager) {
    int choice;
    while (true) {
        displayClientMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                clientManager.displayInfo();
                break;
            case 2:
                clientManager.inputClient();
                break;
            case 3: {
                int clientId;
                cout << "수정할 고객의 ID: ";
                cin >> clientId;
                clientManager.modifyClient(clientId);
                break;
            }
            case 4: {
                int clientId;
                cout << "삭제할 고객의 ID: ";
                cin >> clientId;
                clientManager.deleteClient(clientId);
                break;
            }
            case 5:
                return;
            default:
                cout << "잘못된 선택입니다." << endl;
        }
    }
}

void handleProductManagement(ProductManager& productManager) {
    int choice;
    while (true) {
        displayProductMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                productManager.displayProducts();
                break;
            case 2:
                productManager.inputProduct();
                break;
            case 3: {
                int productId;
                cout << "삭제할 제품의 ID: ";
                cin >> productId;
                productManager.deleteProduct(productId);
                break;
            }
            case 4: {
                int productId;
                cout << "수정할 제품의 ID: ";
                cin >> productId;
                productManager.modifyProduct(productId);
                break;
            }
            case 5: {
                string category;
                cout << "검색할 카테고리: ";
                cin >> category;
                productManager.getProductByCategory(category);
                break;
            }
            case 6: {
                int price;
                cout << "검색할 가격: ";
                cin >> price;
                productManager.getProductByPrice(price);
                break;
            }
            case 7: {
                int productId, quantity;
                cout << "수량을 업데이트할 제품의 ID: ";
                cin >> productId;
                cout << "새로운 수량: ";
                cin >> quantity;
                productManager.updateProductQuantity(productId, quantity);
                break;
            }
            case 8: {
                int productId;
                cout << "재고를 확인할 제품의 ID: ";
                cin >> productId;
                if (productManager.checkProductAvailability(productId)) {
                    cout << "제품이 재고에 있습니다." << endl;
                } else {
                    cout << "제품이 재고에 없습니다." << endl;
                }
                break;
            }
            case 9:
                return;
            default:
                cout << "잘못된 선택입니다." << endl;
        }
    }
}


int main() {
    ClientManager clientManager;
    ProductManager productManager;
    int choice;

    while (true) {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                handleShopping(clientManager, productManager);
                break;
            case 2:
                handleClientManagement(clientManager);
                break;
            case 3:
                handleProductManagement(productManager);
                break;
            case 4:
                cout << "프로그램을 종료합니다." << endl;
                return 0;
            default:
                cout << "잘못된 선택입니다." << endl;
        }
    }

    return 0;
}