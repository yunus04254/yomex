#include "OrderBook.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

using json = nlohmann::json;

void loadData(OrderBook& orderBook, const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return;
    }

    json data;
    file >> data;

    int idCounter = 1;

    std::cout << "Loading buy orders (bids)..." << std::endl;
    // Parse bids
    for (const auto& order : data["bids"]) {
        double price = std::stod(order[0].get<std::string>());
        double quantity = std::stod(order[1].get<std::string>());

        for (int i = 0; i < order[2].get<int>(); ++i) { // for all orders at P-Q
            if (quantity > 0) {
                orderBook.addOrder(Order(idCounter++, "buy", price, quantity));
                std::cout << "New buy order: Price = " << price << ", Quantity = " << quantity << std::endl;
            }
        }
    }

    std::cout << "Loading sell orders (asks)..." << std::endl;
    // Parse asks
    for (const auto& order : data["asks"]) {
        double price = std::stod(order[0].get<std::string>());
        double quantity = std::stod(order[1].get<std::string>());

        for (int i = 0; i < order[2].get<int>(); ++i) { // for all orders at P-Q
            if (quantity > 0) {
                orderBook.addOrder(Order(idCounter++, "sell", price, quantity));
                std::cout << "New sell order: Price = " << price << ", Quantity = " << quantity << std::endl;
            }
        }
    }
}

void displayMatchedOrders(const std::vector<Order>& matches) {
    std::cout << std::setw(10) << "Buy ID"
              << std::setw(15) << "Buy Price"
              << std::setw(15) << "Buy Quantity"
              << std::setw(10) << "Sell ID"
              << std::setw(15) << "Sell Price"
              << std::setw(15) << "Sell Quantity"
              << std::endl;

    std::cout << std::string(80, '-') << std::endl;

    for (size_t i = 0; i < matches.size(); i += 2) {
        const Order& buyOrder = matches[i];
        const Order& sellOrder = matches[i + 1];

        std::cout << std::setw(10) << buyOrder.id
                  << std::setw(15) << std::fixed << std::setprecision(8) << buyOrder.price
                  << std::setw(15) << buyOrder.quantity
                  << std::setw(10) << sellOrder.id
                  << std::setw(15) << std::fixed << std::setprecision(8) << sellOrder.price
                  << std::setw(15) << sellOrder.quantity
                  << std::endl;
    }
}

int main() {
    OrderBook orderBook;
    loadData(orderBook, "data/order_book.json");

    std::cout << "Matching orders..." << std::endl;
    std::vector<Order> matches = orderBook.matchOrders();

    if (matches.empty()) {
        std::cout << "No matches found." << std::endl;
    } else {
        displayMatchedOrders(matches);
    }

    return 0;
}
