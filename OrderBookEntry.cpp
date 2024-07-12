#include <string>
#include "OrderBookEntry.h"


    orderBookEntry::orderBookEntry (double price,double ammount, OrderBookType orderType, 
                    std::string timestamp, std::string products, std::string userName)
    {
        this->price = price;
        this->ammount = ammount;
        this->orderType = orderType;
        this->timestamp = timestamp;
        this->products = products;
        this->userName = userName;
    }

    OrderBookType orderBookEntry::stringToORT (std::string type)
    {
        if (type == "ask") return OrderBookType::ask;
        if (type == "bid") return OrderBookType::bid;

    }

    bool orderBookEntry::compareByTimeStamp (orderBookEntry& e1, orderBookEntry& e2)
    {
        return e1.timestamp < e2.timestamp;
    }

    bool orderBookEntry::compareByPriceAsc (orderBookEntry& e1, orderBookEntry& e2)
    {
        return e1.price < e2.price;
    }
    bool orderBookEntry::compareByPriceDesc (orderBookEntry& e1, orderBookEntry& e2)
    {
        return e1.price > e2.price;
    }

