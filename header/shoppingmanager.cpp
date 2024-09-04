#include "shoppingmanager.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

using namespace std;

ShoppingManager::ShoppingManager(ClientManager& cm, ProductManager& pm)
    : clientManager(cm), productManager(pm), currentClient(nullptr) {}

void ShoppingManager::clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void ShoppingManager::pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void ShoppingManager::displayMainMenu() {
    clearScreen();
    cout << "\033[1;36m*********      섭  팡      *********\033[0m" << endl;
    cout << "\033[1;33m1. 쇼핑하기\033[0m" << endl;
    cout << "\033[1;33m2. 고객 관리\033[0m" << endl;
    cout << "\033[1;33m3. 제품 관리\033[0m" << endl;
    cout << "\033[1;33m4. 프로그램 종료\033[0m" << endl;
    cout << "\033[1;36m************************************\033[0m" << endl;
    cout << "\033[1;32m메뉴를 선택하세요: \033[0m";
}

void ShoppingManager::displayShoppingMenu() {
    clearScreen();
    cout << "\033[1;36m**********    당일배송 쇼핑   **********\033[0m" << endl;
    cout << "\033[1;33m1. 제품 목록 보기\033[0m" << endl;
    cout << "\033[1;33m2. 장바구니에 제품 추가\033[0m" << endl;
    cout << "\033[1;33m3. 장바구니 보기\033[0m" << endl;
    cout << "\033[1;33m4. 주문하기\033[0m" << endl;
    cout << "\033[1;33m5. 로그아웃\033[0m" << endl;
    cout << "\033[1;36m************************************\033[0m" << endl;
    cout << "\033[1;32m메뉴를 선택하세요: \033[0m";
}

void ShoppingManager::displayClientMenu() {
    clearScreen();
    cout << "\033[1;36m**********    고객 관리    **********\033[0m" << endl;
    cout << "\033[1;33m1. 고객 목록 보기\033[0m" << endl;
    cout << "\033[1;33m2. 고객 추가\033[0m" << endl;
    cout << "\033[1;33m3. 고객 정보 수정\033[0m" << endl;
    cout << "\033[1;33m4. 고객 삭제\033[0m" << endl;
    cout << "\033[1;33m5. 메인 메뉴로 돌아가기\033[0m" << endl;
    cout << "\033[1;36m************************************\033[0m" << endl;
    cout << "\033[1;32m메뉴를 선택하세요: \033[0m";
}

void ShoppingManager::displayProductMenu() {
    clearScreen();
    cout << "\033[1;36m**********    제품 관리    **********\033[0m" << endl;
    cout << "\033[1;33m1. 제품 목록 보기\033[0m" << endl;
    cout << "\033[1;33m2. 제품 추가\033[0m" << endl;
    cout << "\033[1;33m3. 제품 삭제\033[0m" << endl;
    cout << "\033[1;33m4. 제품 정보 수정\033[0m" << endl;
    cout << "\033[1;33m5. 카테고리별 제품 검색\033[0m" << endl;
    cout << "\033[1;33m6. 가격별 제품 검색\033[0m" << endl;
    cout << "\033[1;33m7. 제품 수량 업데이트\033[0m" << endl;
    cout << "\033[1;33m8. 제품 재고 확인\033[0m" << endl;
    cout << "\033[1;33m9. 메인 메뉴로 돌아가기\033[0m" << endl;
    cout << "\033[1;36m************************************\033[0m" << endl;
    cout << "\033[1;32m원하는 작업을 선택하세요: \033[0m";
}

int ShoppingManager::getValidInput(int min, int max) {
    int choice;
    while (true) {
        if (cin >> choice && choice >= min && choice <= max) {
            return choice;
        } else {
            cout << "\033[1;31m잘못된 입력입니다. " << min << "에서 " << max << " 사이의 숫자를 입력하세요: \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

Client* ShoppingManager::login() {
    string name, phoneNumber;
    cout << "\033[1;34m이름: \033[0m";
    cin >> name;
    cout << "\033[1;34m전화번호: \033[0m";
    cin >> phoneNumber;
    Client* client = clientManager.login(name, phoneNumber);
    if (client) {
        cout << "\033[1;32m로그인 성공! 환영합니다, " << client->getName() << "님.\033[0m" << endl;
    } else {
        cout << "\033[1;31m로그인 실패. 이름과 전화번호를 확인해주세요.\033[0m" << endl;
    }
    pauseScreen();
    return client;
}

void ShoppingManager::handleShopping() {
    int choice;
    while (true) {
        if (!currentClient) {
            clearScreen();
            cout << "\033[1;36m1. 로그인\033[0m" << endl;
            cout << "\033[1;36m2. 회원가입\033[0m" << endl;
            cout << "\033[1;36m3. 메인 메뉴로 돌아가기\033[0m" << endl;
            cout << "\033[1;32m메뉴를 선택하세요: \033[0m";
            choice = getValidInput(1, 3);
            switch (choice) {
                case 1:
                    currentClient = login();
                    if (!currentClient) continue;
                    break;
                case 2:
                    clearScreen();
                    cout << "\033[1;34m회원가입을 시작합니다.\033[0m" << endl;
                    clientManager.inputClient();
                    cout << "\033[1;32m회원가입이 완료되었습니다. 로그인해주세요.\033[0m" << endl;
                    pauseScreen();
                    continue;
                case 3:
                    return;
            }
        }
        
        displayShoppingMenu();
        choice = getValidInput(1, 5);
        switch (choice) {
            case 1:
                productManager.displayProducts();
                pauseScreen();
                break;
            case 2: {
                int productId, quantity;
                cout << "\033[1;34m제품 ID: \033[0m";
                productId = getValidInput(0, numeric_limits<int>::max());
                cout << "\033[1;34m수량: \033[0m";
                quantity = getValidInput(1, numeric_limits<int>::max());
                Product* product = productManager.search(productId);
                if (product && productManager.checkProductAvailability(productId)) {
                    cart.addItem(product, quantity);
                    cout << "\033[1;32m제품이 장바구니에 추가되었습니다.\033[0m" << endl;
                } else {
                    cout << "\033[1;31m제품이 존재하지 않거나 재고가 부족합니다.\033[0m" << endl;
                }
                pauseScreen();
                break;
            }
            case 3:
                cart.displayCart();
                pauseScreen();
                break;
            case 4:
                if (cart.isEmpty()) {
                    cout << "\033[1;31m장바구니가 비어있습니다.\033[0m" << endl;
                } else {
                    Order order(currentClient->id(), cart);
                    order.process(productManager);
                    cart.clear();
                }
                pauseScreen();
                break;
            case 5:
                cout << "\033[1;33m로그아웃 되었습니다.\033[0m" << endl;
                currentClient = nullptr;
                cart.clear();
                pauseScreen();
                break;
        }
    }
}

void ShoppingManager::handleClientManagement() {
    int choice;
    while (true) {
        displayClientMenu();
        choice = getValidInput(1, 5);
        switch (choice) {
            case 1:
                clientManager.displayInfo();
                pauseScreen();
                break;
            case 2:
                clientManager.inputClient();
                cout << "\033[1;32m고객이 추가되었습니다.\033[0m" << endl;
                pauseScreen();
                break;
            case 3: {
                int clientId;
                cout << "\033[1;34m수정할 고객의 ID: \033[0m";
                clientId = getValidInput(0, numeric_limits<int>::max());
                clientManager.modifyClient(clientId);
                cout << "\033[1;32m고객 정보가 수정되었습니다.\033[0m" << endl;
                pauseScreen();
                break;
            }
            case 4: {
                int clientId;
                cout << "\033[1;34m삭제할 고객의 ID: \033[0m";
                clientId = getValidInput(0, numeric_limits<int>::max());
                clientManager.deleteClient(clientId);
                cout << "\033[1;32m고객이 삭제되었습니다.\033[0m" << endl;
                pauseScreen();
                break;
            }
            case 5:
                return;
        }
    }
}

void ShoppingManager::handleProductManagement() {
    int choice;
    while (true) {
        displayProductMenu();
        choice = getValidInput(1, 9);
        switch (choice) {
            case 1:
                productManager.displayProducts();
                pauseScreen();
                break;
            case 2:
                productManager.inputProduct();
                cout << "\033[1;32m제품이 추가되었습니다.\033[0m" << endl;
                pauseScreen();
                break;
            case 3: {
                int productId;
                cout << "\033[1;34m삭제할 제품의 ID: \033[0m";
                productId = getValidInput(0, numeric_limits<int>::max());
                productManager.deleteProduct(productId);
                cout << "\033[1;32m제품이 삭제되었습니다.\033[0m" << endl;
                pauseScreen();
                break;
            }
            case 4: {
                int productId;
                cout << "\033[1;34m수정할 제품의 ID: \033[0m";
                productId = getValidInput(1, numeric_limits<int>::max());
                productManager.modifyProduct(productId);
                cout << "\033[1;32m제품 정보가 수정되었습니다.\033[0m" << endl;
                pauseScreen();
                break;
            }
            case 5: {
                string category;
                cout << "\033[1;34m검색할 카테고리: \033[0m";
                cin >> category;
                productManager.getProductByCategory(category);
                pauseScreen();
                break;
            }
            case 6: {
                int price;
                cout << "\033[1;34m검색할 가격: \033[0m";
                price = getValidInput(0, numeric_limits<int>::max());
                productManager.getProductByPrice(price);
                pauseScreen();
                break;
            }
            case 7: {
                int productId, quantity;
                cout << "\033[1;34m수량을 업데이트할 제품의 ID: \033[0m";
                productId = getValidInput(0, numeric_limits<int>::max());
                cout << "\033[1;34m새로운 수량: \033[0m";
                quantity = getValidInput(0, numeric_limits<int>::max());
                productManager.updateProductQuantity(productId, quantity);
                cout << "\033[1;32m제품 수량이 업데이트되었습니다.\033[0m" << endl;
                pauseScreen();
                break;
            }
            case 8: {
                int productId;
                cout << "\033[1;34m재고를 확인할 제품의 ID: \033[0m";
                productId = getValidInput(1, numeric_limits<int>::max());
                if (productManager.checkProductAvailability(productId)) {
                    cout << "\033[1;32m제품이 재고에 있습니다.\033[0m" << endl;
                } else {
                    cout << "\033[1;31m제품이 재고에 없습니다.\033[0m" << endl;
                }
                pauseScreen();
                break;
            }
            case 9:
                return;
        }
    }
}

void ShoppingManager::run() {
    int choice;
    while (true) {
        displayMainMenu();
        choice = getValidInput(1, 4);
        switch (choice) {
            case 1:
                handleShopping();
                break;
            case 2:
                handleClientManagement();
                break;
            case 3:
                handleProductManagement();
                break;
            case 4:
                cout << "\033[1;33m프로그램을 종료합니다.\033[0m" << endl;
                return;
        }
    }
}