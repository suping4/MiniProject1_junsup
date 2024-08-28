#ifndef __PRODUCT_MANAGER_H__
#define __PRODUCT_MANAGER_H__

#include <map>
#include <vector>
#include "product.h"

using namespace std;

class ProductManager {
public:
    ProductManager();
    ~ProductManager();

    void inputProduct();
    void addProduct(Product*);
    void deleteProduct(int);
    void modifyProduct(int);
    Product* search(int);
    int makeId();
    void displayProducts();
    void getProductByCategory(string);
    void getProductByPrice(int);
    void updateProductQuantity(int, int);
    bool checkProductAvailability(int);
    vector<string> parseCSV(istream&, char);

    bool displayMenu();

private:
    map<int, Product*> productList;
};

#endif    // __PRODUCT_MANAGER_H__