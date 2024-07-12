#pragma once
#include <string>

enum class OrderBookType {ask,bid,askSale,bidSale};

class orderBookEntry {
    public:
    double price;
    double ammount;
    OrderBookType orderType;
    std::string timestamp;
    std::string products;
    std::string userName;

    orderBookEntry ( double price,double ammount, OrderBookType orderType, 
                     std::string timestamp, std::string products, std::string userName = "dataset");


    static OrderBookType stringToORT (std::string x);
    static bool compareByTimeStamp (orderBookEntry& e1, orderBookEntry& e2);
    static bool compareByPriceAsc (orderBookEntry& e1, orderBookEntry& e2);
    static bool compareByPriceDesc (orderBookEntry& e1, orderBookEntry& e2);
};