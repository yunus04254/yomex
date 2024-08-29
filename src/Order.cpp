#include "Order.h"

Order::Order(int id, const std::string& type, double price, double quantity)
    : id(id), type(type), price(price), quantity(quantity) {}
