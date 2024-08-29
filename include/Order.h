#ifndef ORDER_H
#define ORDER_H

#include <string>

struct Order {
    int id;
    std::string type;
    double price;
    double quantity;

    Order(int id, const std::string& type, double price, double quantity);

    bool operator<(const Order& other) const {
        if (type == "buy") {
            return price < other.price;
        }
        else {
            return price > other.price;
        }
    }
};

#endif
