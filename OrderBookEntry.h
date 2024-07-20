#pragma once
#include <string>

enum class OrderBookType {ask,bid,askSale,bidSale};

// Reresnt an object in our orderbook
//each object is an offer (bid or ask)
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

    //convert string to OrderBookTyoe 
    static OrderBookType stringToORT (std::string x);

    //Compare object by timestamp
    static bool compareByTimeStamp (orderBookEntry& e1, orderBookEntry& e2);

    //Compare object by price ASC
    static bool compareByPriceAsc (orderBookEntry& e1, orderBookEntry& e2);

    //Compare object by price DESC
    static bool compareByPriceDesc (orderBookEntry& e1, orderBookEntry& e2);
};