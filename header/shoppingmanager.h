#ifndef __SHOPPING_MANAGER_H__
#define __SHOPPING_MANAGER_H__

#include "clientmanager.h"
#include "productmanager.h"
#include "cart.h"
#include "order.h"
#include <string>

class ShoppingManager {
public:
    ShoppingManager(ClientManager& cm, ProductManager& pm);
    void run();

private:
    ClientManager& clientManager;
    ProductManager& productManager;
    Cart cart;
    Client* currentClient;

    void displayMainMenu();
    void displayShoppingMenu();
    void displayClientMenu();
    void displayProductMenu();
    int getValidInput(int min, int max);
    void clearScreen();
    void pauseScreen();
    Client* login();
    void handleShopping();
    void handleClientManagement();
    void handleProductManagement();
};

#endif // __SHOPPING_MANAGER_H__