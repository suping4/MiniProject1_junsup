#include <iostream>
#include <string>
#include "client.h"
#include "product.h"
#include "clientmanager.h"
#include "productmanager.h"

using namespace std;

void displayMainMenu() {
    cout << "*** 쇼핑몰 프로그램 *****" << endl;
    cout << "1. 쇼핑몰" << endl;
    cout << "2. 고객 관리" << endl;
    cout << "3. 제품 관리" << endl;
    cout << "4. 프로그램 종료" << endl;
    cout << "어떤 메뉴를 선택하시겠습니까? ";
}

void displayClientMenu() {
    cout << "*** 고객 관리 *****" << endl;
    cout << "1. 입력" << endl;
    cout << "2. 수정" << endl;
    cout << "3. 삭제" << endl;
    cout << "4. 메인 메뉴로 돌아가기" << endl;
    cout << "어떤 항목을 선택하시겠습니까? ";
}

void displayProductMenu() {
    cout << "*** 제품 관리 *****" << endl;
    cout << "1. 입력" << endl;
    cout << "2. 수정" << endl;
    cout << "3. 삭제" << endl;
    cout << "4. 메인 메뉴로 돌아가기" << endl;
    cout << "어떤 항목을 선택하시겠습니까? ";
}

int main() {
    ClientManager clientManager;
    ProductManager productManager;
    int mainChoice, subChoice;

    while (true) {
        displayMainMenu();
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                cout << "쇼핑몰 기능은 아직 구현되지 않았습니다." << endl;
                break;
            case 2:
                while (true) {
                    displayClientMenu();
                    cin >> subChoice;
                    switch (subChoice) {
                        case 1:
                            clientManager.inputClient();
                            break;
                        case 2:
                            clientManager.displayInfo();
                            int clientId;
                            cout << "수정할 고객의 ID를 입력하세요: ";
                            cin >> clientId;
                            clientManager.modifyClient(clientId);
                            break;
                        case 3:
                            clientManager.displayInfo();
                            cout << "삭제할 고객의 ID를 입력하세요: ";
                            cin >> clientId;
                            clientManager.deleteClient(clientId);
                            break;
                        case 4:
                            goto main_menu;
                        default:
                            cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
                    }
                }
                break;
            case 3:
                while (true) {
                    displayProductMenu();
                    cin >> subChoice;
                    switch (subChoice) {
                        case 1:
                            productManager.inputProduct();
                            break;
                        case 2:
                            productManager.displayProducts();
                            int productId;
                            cout << "수정할 제품의 ID를 입력하세요: ";
                            cin >> productId;
                            productManager.modifyProduct(productId);
                            break;
                        case 3:
                            productManager.displayProducts();
                            cout << "삭제할 제품의 ID를 입력하세요: ";
                            cin >> productId;
                            productManager.deleteProduct(productId);
                            break;
                        case 4:
                            goto main_menu;
                        default:
                            cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
                    }
                }
                break;
            case 4:
                cout << "프로그램을 종료합니다." << endl;
                return 0;
            default:
                cout << "잘못된 선택입니다. 다시 선택해주세요." << endl;
        }
        main_menu:;
    }

    return 0;
}