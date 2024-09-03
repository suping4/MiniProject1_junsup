#include "clientmanager.h"
#include "productmanager.h"
#include "shoppingmanager.h"
#include <iostream>

int main() {
    ClientManager clientManager;
    ProductManager productManager;
    ShoppingManager shoppingManager(clientManager, productManager);

    shoppingManager.run();

    return 0;
}