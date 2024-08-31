#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "client.h"
#include "clientmanager.h"

// ClientManager 생성자: 파일에서 고객 정보를 읽어 clientList에 저장
ClientManager::ClientManager() {
    ifstream file;
    file.open("clientlist.txt");  // clientlist.txt 파일 열기
    if(!file.fail()) {  // 파일 열기 성공 시
        while(!file.eof()) {  // 파일 끝까지 읽기
            vector<string> row = parseCSV(file, ',');  // CSV 형식으로 한 줄 파싱
            if(row.size()) {  // 파싱된 데이터가 있으면
                int id = atoi(row[0].c_str());  // 첫 번째 열을 ID로 변환
                Client* c = new Client(id, row[1], row[2], row[3]);  // Client 객체 생성
                clientList.insert( { id, c } );  // clientList에 추가
            }
        }
    }
    file.close( );  // 파일 닫기
}

// ClientManager 소멸자: clientList의 내용을 파일에 저장
ClientManager::~ClientManager() {
    ofstream file;
    file.open("clientlist.txt");  // clientlist.txt 파일 열기
    if(!file.fail()) {  // 파일 열기 성공 시
       for (const auto& v : clientList) {  // clientList의 모든 요소에 대해
           Client* c = v.second;  // Client 객체 포인터 가져오기
           file << c->id() << ", " << c->getName() << ", ";  // ID와 이름 저장
           file << c->getPhoneNumber() << ", ";  // 전화번호 저장
           file << c->getAddress() << endl;  // 주소 저장 후 줄바꿈
       }
    }
    file.close( );  // 파일 닫기
}

// 새로운 고객 정보를 입력받아 추가하는 함수
void ClientManager::inputClient( ) {
    string name, number, address;
    cout << "이름 : "; cin >> name;  // 이름 입력
    cout << "전화번호 : "; cin >> number;  // 전화번호 입력
    cout << "주소 : "; cin.ignore(); getline(cin, address, '\n');  // 주소 입력 (공백 포함)
    
    int id = makeId( );  // 새로운 ID 생성
    Client* c = new Client(id, name, number, address);  // 새 Client 객체 생성
    clientList.insert( { id, c } );  // clientList에 추가
}

// ID로 고객을 검색하는 함수
Client* ClientManager::search(int id) {
    return clientList[id];  // 해당 ID의 Client 객체 포인터 반환
}

// 지정된 키(ID)의 고객을 삭제하는 함수
void ClientManager::deleteClient(int key) {
    clientList.erase(key);  // clientList에서 해당 키의 요소 삭제
}

// 지정된 키(ID)의 고객 정보를 수정하는 함수
void ClientManager::modifyClient(int key) {
    Client* c = search(key);  // 해당 ID의 Client 객체 검색
    // 현재 고객 정보 출력
    cout << "  ID  |     이름     |    전화번호  |      주소" << endl;
    cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
    cout << setw(12) << setfill(' ') << c->getName() << " | ";
    cout << setw(12) << c->getPhoneNumber() << " | ";
    cout << c->getAddress() << endl;
    
    string name, number, address;
    cout << "이름 : "; cin >> name;  // 새 이름 입력
    cout << "전화번호 : "; cin >> number;  // 새 전화번호 입력
    cout << "주소 : "; cin.ignore(); getline(cin, address, '\n');  // 새 주소 입력
    
    c->setName(name);  // 이름 업데이트
    c->setPhoneNumber(number);  // 전화번호 업데이트
    c->setAddress(address);  // 주소 업데이트
    clientList[key] = c;  // clientList 업데이트
}

// 모든 고객 정보를 출력하는 함수
void ClientManager::displayInfo() {
    cout << endl << "  ID  |     이름     |    전화번호  |      주소" << endl;
    for (const auto& v : clientList) {  // clientList의 모든 요소에 대해
         Client* c = v.second;  // Client 객체 포인터 가져오기
         cout << setw(5) << setfill('0') << right << c->id() << " | " << left;  // ID 출력
         cout << setw(12) << setfill(' ') << c->getName() << " | ";  // 이름 출력
         cout << setw(12) << c->getPhoneNumber() << " | ";  // 전화번호 출력
         cout << c->getAddress() << endl;  // 주소 출력
    }
}

// 새로운 고객을 추가하는 함수
void ClientManager::addClient(Client* c) {
    clientList.insert( { c->id(), c } );  // clientList에 새 Client 객체 추가
}

// 새로운 고객 ID를 생성하는 함수
int ClientManager::makeId( ) {
    if(clientList.size( ) == 0) {  // clientList가 비어있으면
        return 0;  // ID 0 반환
    } else {
        auto elem = clientList.end();  // clientList의 마지막 요소
        int id = (--elem)->first;  // 마지막 요소의 ID
        return ++id;  // ID에 1을 더해 반환
    }
}

// 이름과 전화번호로 로그인을 시도하는 함수
Client* ClientManager::login(const string& name, const string& phoneNumber) {
    for (const auto& pair : clientList) {  // clientList의 모든 요소에 대해
        Client* client = pair.second;  // Client 객체 포인터 가져오기
        if (client->getName() == name && client->getPhoneNumber() == phoneNumber) {  // 이름과 전화번호가 일치하면
            return client;  // 해당 Client 객체 포인터 반환
        }
    }
    return nullptr;  // 일치하는 고객이 없으면 nullptr 반환
}

// CSV 파일을 파싱하는 함수
vector<string> ClientManager::parseCSV(istream &file, char delimiter) {
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";
    
    while(!file.eof()) {  // 파일 끝까지 읽기
        char c = file.get();  // 한 문자 읽기
        if (c==delimiter || c=='\r' || c=='\n') {  // 구분자나 줄바꿈 문자면
            if(file.peek()=='\n') file.get();  // 다음 문자가 줄바꿈이면 읽기
            string s = ss.str();  // 현재까지의 문자열
            s.erase(0, s.find_first_not_of(t));  // 앞쪽 공백 제거
            s.erase(s.find_last_not_of(t)+1);  // 뒤쪽 공백 제거
            row.push_back(s);  // 결과 벡터에 추가
            ss.str("");  // 스트림 초기화
            if (c!=delimiter) break;  // 구분자가 아니면 루프 종료
        } else {
            ss << c;  // 문자를 스트림에 추가
        }
    }
    return row;  // 파싱된 결과 반환
}