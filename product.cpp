#include "product.h"

#include <iostream>

using namespace std;

Product::Product(int id, string name, string category, int price, int quantity)
    : m_id(id), m_name(name), m_category(category), m_price(price), m_quantity(quantity) {}

string Product::getName() const {
    return m_name;
}

void Product::setName(string& name) {
    m_name = name;
}

string Product::getCategory() const {
    return m_category;
}

void Product::setCategory(string& category) {
    m_category = category;
}

int Product::getPrice() const {
    return m_price;
}

void Product::setPrice(int price) {
    m_price = price;
}

int Product::getQuantity() const {
    return m_quantity;
}

void Product::setQuantity(int quantity) {
    m_quantity = quantity;
}

int Product::id() const {
    return m_id;
}

bool Product::operator==(const Product &other) const {
    return m_id == other.m_id;
}