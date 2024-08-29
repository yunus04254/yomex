#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "Order.h"
#include <vector>
#include <map>
#include <queue>

class OrderBook {
public:
    void addOrder(const Order& order);
    void cancelOrder(int orderId);
    std::vector<Order> matchOrders();

private:
    std::map<double, std::priority_queue<Order>> buyOrders;
    std::map<double, std::priority_queue<Order>> sellOrders;
};

#endif