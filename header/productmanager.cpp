#include <vector>      // vector 컨테이너를 사용하기 위한 헤더
#include <algorithm>   // 알고리즘 함수들을 사용하기 위한 헤더
#include <fstream>     // 파일 입출력을 위한 헤더
#include <sstream>     // 문자열 스트림 처리를 위한 헤더
#include <iomanip>     // 입출력 조작을 위한 헤더

#include "product.h"         // Product 클래스 정의를 포함
#include "productmanager.h"  // ProductManager 클래스 선언을 포함

using namespace std;  // 표준 네임스페이스 사용

ProductManager::ProductManager()
{
    ifstream file;  // 파일 입력 스트림 객체 생성
    file.open("productlist.txt");  // "productlist.txt" 파일 열기
    if(!file.fail()) {  // 파일 열기에 성공했다면
        while(!file.eof()) {  // 파일의 끝에 도달할 때까지 반복
            vector<string> row = parseCSV(file, ',');  // CSV 파일의 한 행을 파싱
            if(row.size()) {  // 파싱된 행에 데이터가 있다면
                int id = atoi(row[0].c_str());  // 첫 번째 열을 ID로 변환
                // 새 Product 객체 생성
                Product* p = new Product(id, row[1], row[2], atoi(row[3].c_str()), atoi(row[4].c_str()));
                productList.insert({id, p});  // productList에 새 제품 추가
            }
        }
    }
    file.close();  // 파일 닫기
}

ProductManager::~ProductManager()
{
    ofstream file;  // 파일 출력 스트림 객체 생성
    file.open("productlist.txt");  // "productlist.txt" 파일 열기
    if(!file.fail()) {  // 파일 열기에 성공했다면
        for (const auto& v : productList) {  // productList의 모든 요소에 대해
            Product* p = v.second;  // 제품 포인터 가져오기
            // 제품 정보를 CSV 형식으로 파일에 쓰기
            file << p->id() << ", " << p->getName() << ", " << p->getCategory() << ", " << p->getPrice() << ", " << p->getQuantity() << endl;
        }
    }
    file.close();  // 파일 닫기
}

void ProductManager::inputProduct()
{
    string name, category;
    int price, quantity;
    cout << "품명 : "; cin >> name;        // 제품명 입력
    cout << "카테고리 : "; cin >> category;  // 카테고리 입력
    cout << "가격 : "; cin >> price;       // 가격 입력
    cout << "수량 : "; cin >> quantity;    // 수량 입력

    int id = makeId();  // 새 ID 생성
    Product* p = new Product(id, name, category, price, quantity);  // 새 Product 객체 생성
    productList.insert({id, p});  // productList에 새 제품 추가
}

Product* ProductManager::search(int id)
{
    return productList[id];  // 주어진 ID에 해당하는 제품 반환
}

void ProductManager::deleteProduct(int id)
{
    productList.erase(id);  // 주어진 ID의 제품을 productList에서 삭제
}

void ProductManager::modifyProduct(int id)
{
    Product* p = search(id);  // 주어진 ID의 제품 검색
    // 현재 제품 정보 출력
    cout << "  ID  |     품명     |   카테고리   |  가격 |  수량" << endl;
    cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getName() << " | ";
    cout << setw(12) << p->getCategory() << " | ";
    cout << setw(5) << p->getPrice() << " | ";
    cout << setw(5) << p->getQuantity() << endl;

    string name, category;
    int price, quantity;
    cout << "품명 : "; cin >> name;        // 새 제품명 입력
    cout << "카테고리 : "; cin >> category;  // 새 카테고리 입력
    cout << "가격 : "; cin >> price;       // 새 가격 입력
    cout << "수량 : "; cin >> quantity;    // 새 수량 입력

    // 제품 정보 업데이트
    p->setName(name);
    p->setCategory(category);
    p->setPrice(price);
    p->setQuantity(quantity);
}

void ProductManager::displayProducts()
{
    cout << endl << "  ID  |     품명     |   카테고리   |  가격 |  수량" << endl;
    for (const auto& v : productList) {  // productList의 모든 요소에 대해
        Product* p = v.second;  // 제품 포인터 가져오기
        // 제품 정보 출력
        cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getName() << " | ";
        cout << setw(12) << p->getCategory() << " | ";
        cout << setw(5) << p->getPrice() << " | ";
        cout << setw(5) << p->getQuantity() << endl;
    }
}

void ProductManager::getProductByCategory(string category) {
    cout << endl << "  ID  |     품명     |   카테고리   |  가격 |  수량" << endl;
    for (const auto& v : productList) {  // productList의 모든 요소에 대해
        Product* p = v.second;  // 제품 포인터 가져오기
        if (p->getCategory() == category) {  // 카테고리가 일치하면
            // 제품 정보 출력
            cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
            cout << setw(12) << setfill(' ') << p->getName() << " | ";
            cout << setw(12) << p->getCategory() << " | ";
            cout << setw(5) << p->getPrice() << " | ";
            cout << setw(5) << p->getQuantity() << endl;
        }
    }
}

void ProductManager::getProductByPrice(int price) {
    cout << endl << "  ID  |     품명     |   카테고리   |  가격 |  수량" << endl;
    for (const auto& v : productList) {  // productList의 모든 요소에 대해
        Product* p = v.second;  // 제품 포인터 가져오기
        if (p->getPrice() == price) {  // 가격이 일치하면
            // 제품 정보 출력
            cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
            cout << setw(12) << setfill(' ') << p->getName() << " | ";
            cout << setw(12) << p->getCategory() << " | ";
            cout << setw(5) << p->getPrice() << " | ";
            cout << setw(5) << p->getQuantity() << endl;
        }
    }
}

void ProductManager::updateProductQuantity(int id, int quantity) {
    Product* p = search(id);  // 주어진 ID의 제품 검색
    if (p != nullptr) {  // 제품이 존재하면
        p->setQuantity(quantity);  // 수량 업데이트
        cout << "제품 수량이 업데이트되었습니다." << endl;
    } else {
        cout << "해당 ID의 제품을 찾을 수 없습니다." << endl;
    }
}

bool ProductManager::checkProductAvailability(int id) {
    Product* p = search(id);  // 주어진 ID의 제품 검색
    if (p != nullptr) {  // 제품이 존재하면
        return p->getQuantity() > 0;  // 수량이 0보다 크면 true 반환
    }
    return false;  // 제품이 없으면 false 반환
}

int ProductManager::makeId()
{
    if (productList.size() == 0) {  // productList가 비어있으면
        return 0;  // 0 반환
    } else {
        auto elem = productList.end();  // productList의 마지막 요소
        int id = (--elem)->first;  // 마지막 요소의 ID
        return ++id;  // ID에 1을 더해 반환
    }
}

vector<string> ProductManager::parseCSV(istream& file, char delimiter)
{
    stringstream ss;  // 문자열 스트림
    vector<string> row;  // 파싱된 데이터를 저장할 vector
    string t = " \n\r\t";  // 제거할 공백 문자들

    while (!file.eof()) {  // 파일의 끝에 도달할 때까지
        char c = file.get();  // 한 문자 읽기
        if (c == delimiter || c == '\r' || c == '\n') {  // 구분자나 줄바꿈을 만나면
            if (file.peek() == '\n') file.get();  // 다음 문자가 줄바꿈이면 건너뛰기
            string s = ss.str();  // 스트림의 내용을 문자열로 변환
            s.erase(0, s.find_first_not_of(t));  // 앞쪽 공백 제거
            s.erase(s.find_last_not_of(t) + 1);  // 뒤쪽 공백 제거
            row.push_back(s);  // 파싱된 문자열을 vector에 추가
            ss.str("");  // 스트림 초기화
            if (c!= delimiter) break;  // 구분자가 아니면 (즉, 줄바꿈이면) 반복 종료
        } else {
            ss << c;  // 문자를 스트림에 추가
        }
    }
    return row;  // 파싱된 데이터 반환
}