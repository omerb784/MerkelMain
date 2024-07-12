
#include <iostream>
#include "CSVReader.h"
#include <fstream>

CSVReader::CSVReader ()
{

}


std::vector<orderBookEntry> CSVReader::readCSV ()
{
    std::vector<orderBookEntry> entreins;
    std::ifstream csvFile {"market.csv"};
    std::string line;
    std::vector<std::string> tokens;

   if (csvFile.is_open())
   {
      std::cout << "open" << std::endl;

      while (std::getline(csvFile, line))
      {
        try
        {
         tokens = CSVReader::tokenise (line, ',');
         entreins.push_back(CSVReader::stringToOBE(tokens));
        }
        catch (const std::exception e)
        {
            std::cout <<"readCSV: bad data" <<std::endl;
        }
      }

      csvFile.close();
   }
   else
   {
      std::cout << "close" << std::endl;

   }
    return entreins;

}

std::vector<std::string> CSVReader::tokenise (std::string csvLine, char seperator)
{
   std::vector<std::string> tokens;
   signed int start, end;
   std::string token;

   start = csvLine.find_first_not_of(seperator,0);
  
   do
      {
         end = csvLine.find_first_of(seperator,start);

         if (start == csvLine.length() || start == end) break;

         if (end>=0) token = csvLine.substr(start, end - start);

         else token = csvLine.substr(start, csvLine.length() - start);

         tokens.push_back(token);

         start = end+1;
      } 
      while (end > 0);
   
   return tokens;

}
orderBookEntry CSVReader::stringToOBE (std::vector<std::string> tokens)
{
    
    
        double price, ammount;
         
         if (tokens.size() != 5)
         {
            std::cout << "orderbBookEntryCSV: Bad line, skip" << std::endl;
            throw std::exception{};
         }

         try{
          price = std::stod(tokens[3]);
          ammount = std::stod(tokens[4]); 

         } catch (const std::exception e)
         {
            std::cout << "orderbBookEntryCSV: Bad line,  Price/Ammount must be numeric, skip" << std::endl;
            throw;
         }

         orderBookEntry obj(price,ammount,orderBookEntry::stringToORT(tokens[2]),tokens[0],tokens[1]);

    return obj;


}

 orderBookEntry CSVReader::stringToObeUI (std::vector<std::string> tokens, OrderBookType type, std::string curent_time)
 {
         double price, ammount;

         try{
          price = std::stod(tokens[1]);
          ammount = std::stod(tokens[2]); 

         } catch (const std::exception e)
         {
            std::cout << "orderbBookEntryUser: Price/Ammount must be numeric" << std::endl;
            throw;
         }

         orderBookEntry obj(price,ammount,type,curent_time,tokens[0]);

    return obj;
 }
