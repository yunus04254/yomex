#include "OrderBook.h"
#include <algorithm>

void OrderBook::addOrder(const Order& order) {
    if (order.type == "buy") {
        buyOrders[order.price].push(order);
    } else if (order.type == "sell") {
        sellOrders[order.price].push(order);
    }
}

std::vector<Order> OrderBook::matchOrders() {
    std::vector<Order> matchedOrders;

    while (!buyOrders.empty() && !sellOrders.empty()) {
        auto highestBuy = buyOrders.rbegin();
        auto lowestSell = sellOrders.begin();

        if (highestBuy->first >= lowestSell->first) {
            Order buyOrder = highestBuy->second.top();
            Order sellOrder = lowestSell->second.top();

            double matchQuantity = std::min(buyOrder.quantity, sellOrder.quantity);

            // record matched part
            matchedOrders.push_back(Order(buyOrder.id, "buy", buyOrder.price, matchQuantity));
            matchedOrders.push_back(Order(sellOrder.id, "sell", sellOrder.price, matchQuantity));

            // update quantities in orderbook
            buyOrder.quantity -= matchQuantity;
            sellOrder.quantity -= matchQuantity;

            // remove/update buy order
            highestBuy->second.pop();
            if (buyOrder.quantity > 0) {
                highestBuy->second.push(buyOrder);
            }
            if (highestBuy->second.empty()) {
                buyOrders.erase(highestBuy->first);
            }

            // remove/update sell order
            lowestSell->second.pop();
            if (sellOrder.quantity > 0) {
                lowestSell->second.push(sellOrder);
            }
            if (lowestSell->second.empty()) {
                sellOrders.erase(lowestSell->first);
            }
        } else {
            break;
        }
    }
    return matchedOrders;
}
