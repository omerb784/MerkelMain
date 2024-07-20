#pragma once

#include "OrderBookEntry.h"
#include <vector>

// this class used to translete csv data into an object
//translete csv data/user input into an OrderBookEntry object.
class CSVReader{

    public:

        CSVReader();

         //  read csv data, toknise and push it to an object
        static std::vector<orderBookEntry> readCSV();

        // Tokenise the data from csv file using seperator
        static std::vector<std::string> tokenise (std::string csvLine, char seperator); 
        
        // User bid/ask transform into orderbookEntry        
        static orderBookEntry stringToObeUI (std::vector<std::string> tokens, OrderBookType type, std::string cuurent_time); 


    private:
        // transform tokenise CSV data into an orderbookEntry
        static orderBookEntry stringToOBE (std::vector<std::string> tokens);  





};
