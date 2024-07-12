#pragma once

#include "OrderBookEntry.h"
#include <vector>

// this class used to translete csv data into an object
class CSVReader{

    public:

        CSVReader();

        static std::vector<orderBookEntry> readCSV(); //  read csv data, toknise and push it to an object

        static std::vector<std::string> tokenise (std::string csvLine, char seperator); // Tokenise the data from csv file using seperator

        static orderBookEntry stringToObeUI (std::vector<std::string> tokens, OrderBookType type, std::string cuurent_time); // User bid/ask transform into orderbookEntry        


    private:
        static orderBookEntry stringToOBE (std::vector<std::string> tokens);  // transform tokenise CSV data into an orderbookEntry





};
