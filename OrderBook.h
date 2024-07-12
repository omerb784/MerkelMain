#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

// This class is the app order book, include function of operation that can be used on the order book
class OrderBook
{
   public:
     
      OrderBook ();
      std::vector<std::string> getKnownProducts (); // get all product available in the order book

      std::vector<orderBookEntry> getOrders (OrderBookType type,
                                             std::string product,
                                             std::string tinestamp); // Get spesific entries filterd by type,
                                                                     //product and the current time stamp

      std::string getEarliestTime (); // when the app start, this fuction returens the start time in orderbook

      std::string getNextTime (std::string timestamp); // returens the next time stamp in the orderbook

      static double getHighestPrice (std::vector<orderBookEntry>& entries); // returnes the highest bid price for spesific product in current timestamp

      static double getLowestPrice (std::vector<orderBookEntry>& entries); // returnes the lowest ask price for spesific product in current timestamp

      double getHighestPriceChange (std::string product, std::string currnetTime); // returnes the highest bid price change for spesific product 
                                                                                   // from previous timestamp to the current timestamp 

      double getLowestPriceChange (std::string product, std::string currnetTime); // returnes the lowest ask price change for spesific product 
                                                                                   // from previous timestamp to the current timestamp 

      void insertOrder (orderBookEntry& order); // insert a user bid/ask into orderbook

      std::vector<orderBookEntry> matchAskToBid (std::string timestamp, std::string product); // when we move to next timestamp this function match bids to asks

   private:
      
      std::vector<orderBookEntry> orders; // the whole orderbook, contain all asks and bids


};

