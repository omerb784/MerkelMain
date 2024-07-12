#include "OrderBook.h"
#include "CSVReader.h"
#include <iostream>
#include <map>
#include <algorithm>


    OrderBook::OrderBook ()
    {
        orders = CSVReader::readCSV();
    }

    std::vector<std::string> OrderBook::getKnownProducts ()
    {
        std::vector<std::string> products;

        std::map<std::string,bool> prodMap;

        for (orderBookEntry& temp : orders)
        {
            prodMap[temp.products] = true;
        }

        for (auto const& e : prodMap)
        {
            products.push_back(e.first);
        }

        return products;

    }
    std::vector<orderBookEntry> OrderBook::getOrders (OrderBookType type,
                                            std::string product,
                                            std::string tinestamp)
    {
        std::vector<orderBookEntry> orders_sub;
        for (const orderBookEntry& temp : orders)
        {
            if (temp.orderType == type &&
                temp.products == product &&
                temp.timestamp == tinestamp)
                {
                    orders_sub.push_back(temp);
                }
        }
        return orders_sub;

    }




    double OrderBook::getHighestPrice (std::vector<orderBookEntry>& entries)
    {
        double max = entries.at(0).price;
        for (orderBookEntry& temp : entries)
        {
            if (temp.price > max) max = temp.price;
        }

        return max;  
    }

    
    double OrderBook::getLowestPrice (std::vector<orderBookEntry>& entries)
    {
        double min = entries.at(0).price;
        for (orderBookEntry& temp : entries)
        {
            if (temp.price < min) min = temp.price;
        }

        return min;  
    }


    std::string OrderBook::getEarliestTime ()
    {
        return orders.at(0).timestamp;
    }

    std::string OrderBook::getNextTime(std::string timestamp)
    {
        std::string next_timestamp = "";
        for (orderBookEntry& temp : orders)
        {
            if (temp.timestamp > timestamp)
            {
                next_timestamp = temp.timestamp;
                break;
            }
        }
        if (next_timestamp == "")
        {
            next_timestamp = orders.at(0).timestamp;
        }  

        return next_timestamp;
    }

    double OrderBook::getHighestPriceChange (std::string product, std::string currnetTime)
    {
        std::vector<orderBookEntry> currentTimestemp = getOrders(OrderBookType::bid,product, currnetTime);
        std::vector<orderBookEntry> nextTimestemp = getOrders(OrderBookType::bid,product, getNextTime(currnetTime));
        return getHighestPrice(nextTimestemp) - getHighestPrice(currentTimestemp);


    }
    double OrderBook::getLowestPriceChange (std::string product, std::string currnetTime)
    {
        std::vector<orderBookEntry> currentTimestemp = getOrders(OrderBookType::ask,product, currnetTime);
        std::vector<orderBookEntry> nextTimestemp = getOrders(OrderBookType::ask,product, getNextTime(currnetTime));
        return getLowestPrice(nextTimestemp)  - getLowestPrice(currentTimestemp);
    }
    

      void OrderBook::insertOrder (orderBookEntry& order)
      {
        orders.push_back(order);
        std::sort(orders.begin(), orders.end(), orderBookEntry::compareByTimeStamp);
      }


      std::vector<orderBookEntry> OrderBook::matchAskToBid (std::string timestamp, std::string product)
      {
        std::vector <orderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
        std::vector <orderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);

        std::vector <orderBookEntry> sales;
        std::sort(asks.begin(), asks.end(), orderBookEntry::compareByPriceAsc);
        std::sort(bids.begin(), bids.end(), orderBookEntry::compareByPriceDesc);

        for (orderBookEntry& ask : asks)
        {
            for (orderBookEntry& bid: bids)
            {
                if (bid.price >= ask.price && bid.ammount > 0)
                {
                    std::cout << ask.userName << " bid " << bid.userName << std::endl;
                    orderBookEntry sale (ask.price, 0,  OrderBookType::askSale, timestamp, product);
                    if (bid.userName == "simuser")
                    {
                        sale.orderType = OrderBookType::bidSale;
                        sale.userName = "simuser";
                    }
                    if(ask.userName == "simuser")
                        sale.userName = "simuser";
                     std::cout << sale.price << std::endl; 
                    

                    if (bid.ammount == ask.ammount)
                    {
                        sale.ammount = ask.ammount;
                        sales.push_back(sale);
                        bid.ammount = 0;
                        break;
                    }
                    
                    if (bid.ammount > ask.ammount)
                    {
                        sale.ammount = ask.ammount;
                        sales.push_back(sale);
                        bid.ammount = bid.ammount- ask.ammount;
                        break;
                    }

                    
                    if (bid.ammount < ask.ammount)
                    {
                        sale.ammount = bid.ammount;
                        ask.ammount = ask.ammount - bid.ammount;
                        bid.ammount = 0;
                        sales.push_back(sale);
                        continue;
                    }
                }
            }
        }

        return sales;

        

      }



