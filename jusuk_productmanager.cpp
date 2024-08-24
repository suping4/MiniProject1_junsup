/*
#include <vector> // 벡터 라이브러리를 포함합니다.
#include <algorithm> // 알고리즘 라이브러리를 포함합니다.
#include <fstream> // 파일 입출력 라이브러리를 포함합니다.
#include <sstream> // 문자열 스트림 라이브러리를 포함합니다.
#include <iomanip> // 입출력 조작자 라이브러리를 포함합니다.

#include "product.h" // Product 클래스를 포함합니다.
#include "productmanager.h" // ProductManager 클래스를 포함합니다.

using namespace std; // 표준 네임스페이스를 사용합니다.

// ProductManager 클래스의 생성자
ProductManager::ProductManager()
{
    ifstream file; // 파일 스트림 객체를 선언합니다.
    file.open("productlist.txt"); // "productlist.txt" 파일을 열어줍니다.
    if(!file.fail()) { // 파일 열기에 실패하지 않았는지 확인합니다.
        while(!file.eof()) { // 파일의 끝까지 반복합니다.
            vector<string> row = parseCSV(file, ','); // CSV 파일을 파싱하여 벡터로 저장합니다.
            if(row.size()) { // 벡터가 비어있지 않은 경우
                int id = atoi(row.c_str()); // 첫 번째 요소를 ID로 변환합니다.
                Product* p = new Product(id, row, row, atoi(row.c_str()), atoi(row.c_str())); // Product 객체를 생성합니다.
                productList.insert({id, p}); // productList에 Product 객체를 삽입합니다.
            }
        }
    }
    file.close(); // 파일을 닫습니다.
}

// ProductManager 클래스의 소멸자
ProductManager::~ProductManager()
{
    ofstream file; // 파일 스트림 객체를 선언합니다.
    file.open("productlist.txt"); // "productlist.txt" 파일을 열어줍니다.
    if(!file.fail()) { // 파일 열기에 실패하지 않았는지 확인합니다.
        for (const auto& v : productList) { // productList의 모든 요소를 반복합니다.
            Product* p = v.second; // Product 객체를 가져옵니다.
            file << p->id() << ", " << p->getName() << ", " << p->getCategory() << ", " << p->getPrice() << ", " << p->getQuantity() << endl; // 파일에 Product 정보를 작성합니다.
        }
    }
    file.close(); // 파일을 닫습니다.
}

// 새로운 상품을 입력하는 함수
void ProductManager::inputProduct()
{
    string name, category; // 상품 이름과 카테고리를 저장할 변수를 선언합니다.
    int price, quantity; // 상품 가격과 수량을 저장할 변수를 선언합니다.
    cout << "name : "; cin >> name; // 사용자로부터 상품 이름을 입력받습니다.
    cout << "category : "; cin >> category; // 사용자로부터 상품 카테고리를 입력받습니다.
    cout << "price : "; cin >> price; // 사용자로부터 상품 가격을 입력받습니다.
    cout << "quantity : "; cin >> quantity; // 사용자로부터 상품 수량을 입력받습니다.

    int id = makeId(); // 새로운 ID를 생성합니다.
    Product* p = new Product(id, name, category, price, quantity); // Product 객체를 생성합니다.
    productList.insert({id, p}); // productList에 Product 객체를 삽입합니다.
}

// 특정 ID의 상품을 검색하는 함수
Product* ProductManager::search(int id)
{
    return productList[id]; // 해당 ID의 Product 객체를 반환합니다.
}

// 특정 ID의 상품을 삭제하는 함수
void ProductManager::deleteProduct(int id)
{
    productList.erase(id); // 해당 ID의 Product 객체를 삭제합니다.
}

// 특정 ID의 상품을 수정하는 함수
void ProductManager::modifyProduct(int id)
{
    Product* p = search(id); // 해당 ID의 Product 객체를 검색합니다.
    cout << "  ID  |     Name     | Category | Price | Quantity" << endl; // 수정할 상품 정보를 출력합니다.
    cout << setw(5) << setfill('0') << right << p->id() << " | " << left; // ID를 출력합니다.
    cout << setw(12) << setfill(' ') << p->getName() << " | "; // 이름을 출력합니다.
    cout << setw(12) << p->getCategory() << " | "; // 카테고리를 출력합니다.
    cout << setw(5) << p->getPrice() << " | "; // 가격을 출력합니다.
    cout << setw(5) << p->getQuantity() << endl; // 수량을 출력합니다.

    string name, category; // 새로운 이름과 카테고리를 저장할 변수를 선언합니다.
    int price, quantity; // 새로운 가격과 수량을 저장할 변수를 선언합니다.
    cout << "name : "; cin >> name; // 사용자로부터 새로운 이름을 입력받습니다.
    cout << "category : "; cin >> category; // 사용자로부터 새로운 카테고리를 입력받습니다.
    cout << "price : "; cin >> price; // 사용자로부터 새로운 가격을 입력받습니다.
    cout << "quantity : "; cin >> quantity; // 사용자로부터 새로운 수량을 입력받습니다.

    p->setName(name); // Product 객체의 이름을 수정합니다.
    p->setCategory(category); // Product 객체의 카테고리를 수정합니다.
    p->setPrice(price); // Product 객체의 가격을 수정합니다.
    p->setQuantity(quantity); // Product 객체의 수량을 수정합니다.
}

// 모든 상품을 출력하는 함수
void ProductManager::displayProducts()
{
    cout << endl << "  ID  |     Name     | Category | Price | Quantity" << endl; // 상품 목록 헤더를 출력합니다.
    for (const auto& v : productList) { // productList의 모든 요소를 반복합니다.
        Product* p = v.second; // Product 객체를 가져옵니다.
        cout << setw(5) << setfill('0') << right << p->id() << " | " << left; // ID를 출력합니다.
        cout << setw(12) << setfill(' ') << p->getName() << " | "; // 이름을 출력합니다.
        cout << setw(12) << p->getCategory() << " | "; // 카테고리를 출력합니다.
        cout << setw(5) << p->getPrice() << " | "; // 가격을 출력합니다.
        cout << setw(5) << p->getQuantity() << endl; // 수량을 출력합니다.
    }
}

// 특정 카테고리의 상품을 출력하는 함수
void ProductManager::getProductByCategory(string category)
{
    cout << endl << "  ID  |     Name     | Category | Price | Quantity" << endl; // 상품 목록 헤더를 출력합니다.
    for (const auto& v : productList) { // productList의 모든 요소를 반복합니다.
        Product* p = v.second; // Product 객체를 가져옵니다.
        if (p->getCategory() == category) { // 해당 카테고리의 상품인지 확인합니다.
            cout << setw(5) << setfill('0') << right << p->id() << " | " << left; // ID를 출력합니다.
            cout << setw(12) << setfill(' ') << p->getName() << " | "; // 이름을 출력합니다.
            cout << setw(12) << p->getCategory() << " | "; // 카테고리를 출력합니다.
            cout << setw(5) << p->getPrice() << " | "; // 가격을 출력합니다.
            cout << setw(5) << p->getQuantity() << endl; // 수량을 출력합니다.
        }
    }
}

// 특정 가격의 상품을 출력하는 함수
void ProductManager::getProductByPrice(int price)
{
    cout << endl << "  ID  |     Name     | Category | Price | Quantity" << endl; // 상품 목록 헤더를 출력합니다.
    for (const auto& v : productList) { // productList의 모든 요소를 반복합니다.
        Product* p = v.second; // Product 객체를 가져옵니다.
        if (p->getPrice() == price) { // 해당 가격의 상품인지 확인합니다.
            cout << setw(5) << setfill('0') << right << p->id() << " | " << left; // ID를 출력합니다.
            cout << setw(12) << setfill(' ') << p->getName() << " | "; // 이름을 출력합니다.
            cout << setw(12) << p->getCategory() << " | "; // 카테고리를 출력합니다.
            cout << setw(5) << p->getPrice() << " | "; // 가격을 출력합니다.
            cout << setw(5) << p->getQuantity() << endl; // 수량을 출력합니다.
        }
    }
}

// 특정 ID의 상품 수량을 업데이트하는 함수
void ProductManager::updateProductQuantity(int id, int quantity)
{
    Product* p = search(id); // 해당 ID의 Product 객체를 검색합니다.
    p->setQuantity(quantity); // Product 객체의 수량을 업데이트합니다.
}

// 특정 ID의 상품이 사용 가능한지 확인하는 함수
bool ProductManager::checkProductAvailability(int id)
{
    Product* p = search(id); // 해당 ID의 Product 객체를 검색합니다.
    return p->getQuantity() > 0; // 수량이 0보다 큰지 확인합니다.
}

// 새로운 ID를 생성하는 함수
int ProductManager::makeId()
{
    if (productList.size() == 0) { // productList가 비어 있는지 확인합니다.
        return 0; // 비어 있을 경우 0을 반환합니다.
    } else {
        auto elem = productList.end(); // productList의 끝을 가리키는 반복자를 가져옵니다.
        int id = (--elem)->first; // 이전 요소의 ID를 가져옵니다.
        return ++id; // ID를 증가시켜 반환합니다.
    }
}

// CSV 파일을 파싱하는 함수
vector<string> ProductManager::parseCSV(istream& file, char delimiter)
{
    stringstream ss; // 문자열 스트림 객체를 선언합니다.
    vector<string> row; // 파싱된 데이터를 저장할 벡터를 선언합니다.
    string t = " \n\r\t"; // 공백 문자를 저장할 변수를 선언합니다.

    while (!file.eof()) { // 파일의 끝까지 반복합니다.
        char c = file.get(); // 파일에서 한 문자를 읽어옵니다.
        if (c == delimiter || c == '\r' || c == '\n') { // 구분자 또는 줄바꿈 문자를 만났는지 확인합니다.
            if (file.peek() == '\n') file.get(); // 줄바꿈 문자를 만났다면 다음 문자를 읽어옵니다.
            string s = ss.str(); // 문자열 스트림에서 문자열을 가져옵니다.
            s.erase(0, s.find_first_not_of(t)); // 앞의 공백 문자를 제거합니다.
            s.erase(s.find_last_not_of(t) + 1); // 뒤의 공백 문자를 제거합니다.
            row.push_back(s); // 파싱된 데이터를 벡터에 추가합니다.
            ss.str(""); // 문자열 스트림을 초기화합니다.
            if (c!= delimiter) break; // 구분자가 아니라면 반복을 종료합니다.
        } else {
            ss << c; // 문자열 스트림에 문자를 추가합니다.
        }
    }
    return row; // 파싱된 데이터를 반환합니다.
}

// 메뉴를 출력하고 사용자의 선택을 처리하는 함수
bool ProductManager::displayMenu()
{
    int ch, key; // 사용자의 선택을 저장할 변수를 선언합니다.
    string category; // 카테고리를 저장할 변수를 선언합니다.
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl; // 메뉴 헤더를 출력합니다.
    cout << "              Product Manager                 " << endl; // 메뉴 제목을 출력합니다.
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl; // 메뉴 헤더를 출력합니다.
    cout << "  1. Display Product List                     " << endl; // 1번 메뉴를 출력합니다.
    cout << "  2. Input Product                            " << endl; // 2번 메뉴를 출력합니다.
    cout << "  3. Delete Product                           " << endl; // 3번 메뉴를 출력합니다.
    cout << "  4. Modify Product                           " << endl; // 4번 메뉴를 출력합니다.
    cout << "  5. Search Product by Category               " << endl; // 5번 메뉴를 출력합니다.
    cout << "  6. Search Product by Price                  " << endl; // 6번 메뉴를 출력합니다.
    cout << "  7. Update Product Quantity                  " << endl; // 7번 메뉴를 출력합니다.
    cout << "  8. Check Product Availability               " << endl; // 8번 메뉴를 출력합니다.
    cout << "  9. Quit this Program                        " << endl; // 9번 메뉴를 출력합니다.
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl; // 메뉴 헤더를 출력합니다.
    cout << " What do you wanna do? "; // 사용자에게 선택지를 묻습니다.
    cin >> ch; // 사용자의 선택을 입력받습니다.
    switch (ch) { // 사용자의 선택에 따라 처리합니다.
        case 1:
            displayProducts(); // 모든 상품을 출력합니다.
            cin.ignore(); // 입력 버퍼를 초기화합니다.
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 2:
            inputProduct(); // 새로운 상품을 입력합니다.
            break;
        case 3:
            displayProducts(); // 모든 상품을 출력합니다.
            cout << "   Choose Key : "; // 사용자에게 키를 선택하도록 요청합니다.
            cin >> key; // 사용자의 선택을 입력받습니다.
            deleteProduct(key); // 선택한 키의 상품을 삭제합니다.
            break;
        case 4:
            displayProducts(); // 모든 상품을 출력합니다.
            cout << "   Choose Key : "; // 사용자에게 키를 선택하도록 요청합니다.
            cin >> key; // 사용자의 선택을 입력받습니다.
            modifyProduct(key); // 선택한 키의 상품을 수정합니다.
            break;
        case 5:
            cout << "   Enter Category : "; // 사용자에게 카테고리를 입력하도록 요청합니다.
            cin >> category; // 사용자의 선택을 입력받습니다.
            getProductByCategory(category); // 선택한 카테고리의 상품을 출력합니다.
            cin.ignore(); // 입력 버퍼를 초기화합니다.
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 6:
            cout << "   Enter Price : "; // 사용자에게 가격을 입력하도록 요청합니다.
            int price; // 가격을 저장할 변수를 선언합니다.
            cin >> price; // 사용자의 선택을 입력받습니다.
            getProductByPrice(price); // 선택한 가격의 상품을 출력합니다.
            cin.ignore(); // 입력 버퍼를 초기화합니다.
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 7:
            displayProducts(); // 모든 상품을 출력합니다.
            cout << "   Choose Key : "; // 사용자에게 키를 선택하도록 요청합니다.
            cin >> key; // 사용자의 선택을 입력받습니다.
            cout << "   Enter Quantity : "; // 사용자에게 수량을 입력하도록 요청합니다.
            int quantity; // 수량을 저장할 변수를 선언합니다.
            cin >> quantity; // 사용자의 선택을 입력받습니다.
            updateProductQuantity(key, quantity); // 선택한 키의 상품 수량을 업데이트합니다.
            break;
        case 8:
            displayProducts(); // 모든 상품을 출력합니다.
            cout << "   Choose Key : "; // 사용자에게 키를 선택하도록 요청합니다.
            cin >> key; // 사용자의 선택을 입력받습니다.
            if (checkProductAvailability(key)) { // 선택한 키의 상품이 사용 가능한지 확인합니다.
                cout << "   Product is available." << endl; // 사용 가능한 경우 메시지를 출력합니다.
            } else {
                cout << "   Product is not available." << endl; // 사용 불가능한 경우 메시지를 출력합니다.
            }
            cin.ignore(); // 입력 버퍼를 초기화합니다.
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 9:
            return false; // 프로그램을 종료합니다.
        default:
            displayProducts(); // 모든 상품을 출력합니다.
            cin.ignore(); // 입력 버퍼를 초기화합니다.
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
    }
    return true; // 프로그램을 계속 실행합니다.
}
*/