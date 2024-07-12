#include <iostream>
#include "MerkelMain.h"
#include <vector>
#include <limits>
#include "OrderBookEntry.h"
#include "CSVReader.h"


merkelMain::merkelMain()
{

}

void merkelMain::init ()
{
    int input;
    currnetTime = orderBook.getEarliestTime();
    bool run = true;
            printMenu();
    while (run)
    {
        input = getUserOption();
        run = userProcessO(input);
        printMenu();
    }
}
    
         



void merkelMain::printMenu()
 {

    std::cout << "--------------------------" << std::endl;
    std::cout << currnetTime << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "1: Print help " << std::endl;
    std::cout << "2: Print exchange stats " << std::endl;
    std::cout << "3: Make an ask " << std::endl;
    std::cout << "4: Make a bid " << std::endl;
    std::cout << "5: Print wallet " << std::endl;
    std::cout << "6: Add to wallet " << std::endl;
    std::cout << "9: Continue " << std::endl;
    std::cout << "0: Exit " << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "Select an option " << std::endl <<std::endl;
  }

 int merkelMain::getUserOption ()
 {
     int valid;
     std::string userOption;
     std::getline(std::cin,userOption);
          try
        {
            valid = std::stoi(userOption);
            return valid;
        }
        catch(const std::exception& e)
        {
            return 10;
        }
 } 

 void merkelMain::invalid ()
 {
     std::cout << "Invalid, please enter a valid number"<< std::endl<< std::endl;
 }
 
 void merkelMain::printHelp ()
 {
     std::cout << "Help - your aim is to make money. Analayze the market and make bid and offers"<< std::endl<< std::endl;
     std::cout << "Available products:"<< std::endl<< std::endl;

     for (std::string const& product : orderBook.getKnownProducts())
     {
        std::cout << product << std::endl<< std::endl;
     }
 }

 void merkelMain::marketStats ()
 {

    std::cout << "Timestamp: "<< currnetTime <<std::endl<<std::endl; 
    for (std::string const& s : orderBook.getKnownProducts())
    {
        std::cout << "Product "<< s <<std::endl; 
        std::vector<orderBookEntry> askEntries = orderBook.getOrders(OrderBookType::ask, s, currnetTime) ;
        std::cout << "Asks: "<< askEntries.size() <<std::endl;
        if (askEntries.size() > 0)
        {
            std::cout << "Lowest price for this product: "<< orderBook.getLowestPrice(askEntries) <<std::endl ;
        }
        else std::cout << "No asks for this product" << std::endl;

        std::vector<orderBookEntry> bidEntries = orderBook.getOrders(OrderBookType::bid, s, currnetTime) ;
        std::cout << "Bids: "<< bidEntries.size() <<std::endl;
        if (bidEntries.size() > 0)
        {
            std::cout << "Higest price for this product: "<< orderBook.getHighestPrice(bidEntries) <<std::endl<< std::endl; 
        }
        else std::cout << "No bids for this product " << std::endl<< std::endl;
    }
 }

 void merkelMain::makeAnAsk ()
 {

    std::string input;
    std::cout << "make an ask"<< std::endl;
    std::cout << "Example: DOGE/USDT,0.001,210000"<< std::endl;
    std::getline(std::cin,input);

    std::vector<std::string> tokens = CSVReader::tokenise(input,',');
    if (tokens.size() != 3 ) std::cout<< "Bad line !" << std::endl << "orderbBookEntryUser: Data doesnt match an ask offer, ignore"<< std::endl;
    else
    {
        try{
            bool existProduct = false;    
            orderBookEntry userAsk = CSVReader::stringToObeUI(tokens, OrderBookType::ask,currnetTime);
            for(const std::string& p : orderBook.getKnownProducts())
            {
                if (userAsk.products == p ) 
                {
                    existProduct = true;
                    break;
                }
            }

            if (!existProduct)
            {
                std::cout<< "orderbBookEntryUser: Unknown product, ignore" << std::endl;
                return;
            }

            if (Wallet.currencyAmmountCheck(CSVReader::tokenise(userAsk.products, '/').at(0),userAsk.ammount ))
            {
            std::cout <<"An ask to sell " << userAsk.ammount<< " " << CSVReader::tokenise(userAsk.products, '/').at(0)
            << " in exchange for " << userAsk.price << " " << CSVReader::tokenise(userAsk.products, '/').at(1) <<  " per unit recieved"<<std::endl;
            userAsk.userName = "simuser";
            orderBook.insertOrder(userAsk);
            }
        }    
            catch (const std::exception& e)
            {
                std::cout << "orderbBookEntryUser: Bad line, ignore" << std::endl;
            }
        
    }
 }

 void merkelMain::bid ()
 {
    std::string input;
    std::cout << "make an bid"<< std::endl;
    std::cout << "Example: DOGE/USDT,0.001,210000"<< std::endl;
    std::getline(std::cin,input);

    std::vector<std::string> tokens = CSVReader::tokenise(input,',');
    if (tokens.size() != 3 ) std::cout<< "Bad line !" << std::endl << "orderbBookEntryUser: Data doesnt match an bid offer, ignore"<< std::endl;
    else
    {
        try{
        bool existProduct = false; 
        orderBookEntry userBid = CSVReader::stringToObeUI(tokens, OrderBookType::bid,currnetTime);
        for(const std::string& p : orderBook.getKnownProducts())
        {
            if (userBid.products == p ) 
            {
                existProduct = true;
                break;
            }
        }
        if (existProduct && Wallet.currencyAmmountCheck(CSVReader::tokenise(userBid.products, '/').at(1),userBid.price))
        {
        std::cout << userBid.ammount<< ", " << userBid.price << std::endl;
        userBid.userName = "simuser";
        orderBook.insertOrder(userBid);
        }
        else std::cout<< "orderbBookEntryUser: Unknown product, ignore" << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cout << "orderbBookEntryUser: Bad line, ignore" << std::endl;
        }
    }

  
 }

 void merkelMain::printWallet ()
 {
    std::cout << Wallet.printWallet() << std::endl;
 }

 void merkelMain::addToWallet()
 {
    std::string input;
    std::cout << "Insert currencies to wallet"<< std::endl;
    std::cout << "Example: USDT,210000"<< std::endl;
    std::getline(std::cin,input);

    std::vector<std::string> tokens = CSVReader::tokenise(input,',');
    if (tokens.size() != 2) std::cout<< "Bad line !" << std::endl << "orderbBookEntryUser: Data is not valid"<< std::endl;
    else
    {
        try
        {
            bool existProduct = false;    
            for(const std::string& p : orderBook.getKnownProducts())
            {
                if (tokens.at(0) == CSVReader::tokenise(p, '/').at(0) || tokens.at(0) == CSVReader::tokenise(p, '/').at(1)  ) 
                {
                    existProduct = true;
                    break;
                }
            }

            if (existProduct)
            {
                Wallet.insertMoney(tokens.at(0), std::stod(tokens.at(1)));
                printWallet ();
            }
            else std::cout<< "orderbBookEntryUser: Unknown product, ignore" << std::endl;
        }    
            catch (const std::exception& e)
            {
                std::cout << "orderbBookEntryUser: Bad line, ignore" << std::endl;
            }
        

    }

 
 }


 void merkelMain::nextTimeFrame ()
 {
    std::cout << "Going to next time frame" << std::endl << std::endl;
    for (std::string const& s : orderBook.getKnownProducts())
        {
           std::vector<orderBookEntry> sales =  orderBook.matchAskToBid(currnetTime, s);
           std::cout<<"Trancastion made for: "<<s<< ": " <<sales.size() << std::endl;
           for (orderBookEntry& sale : sales)
           {
                std::cout << "Sale price: " << sale.price << " Sale ammount: " << sale.ammount << " "<< sale.userName << std::endl;
                if (sale.userName == "simuser")
                {
                    if (sale.orderType == OrderBookType::bidSale)
                    {
                        Wallet.insertMoney(CSVReader::tokenise(sale.products, '/').at(0), sale.ammount);
                        Wallet.RemoveMoney(CSVReader::tokenise(sale.products, '/').at(1), sale.ammount*sale.price);
                    }
                    else
                    {
                        Wallet.RemoveMoney(CSVReader::tokenise(sale.products, '/').at(0), sale.ammount);
                        Wallet.insertMoney(CSVReader::tokenise(sale.products, '/').at(1), sale.ammount*sale.price);
                    }
                }
           }

           std::cout << "Highest bid avilable change: " << orderBook.getHighestPriceChange(s,currnetTime) << std::endl;
           std::cout << "Lowest ask avilable change: " << orderBook.getLowestPriceChange(s, currnetTime)<< std::endl << std::endl;         

        }
     
    currnetTime = orderBook.getNextTime(currnetTime);

 }

  void merkelMain::exit ()
 {
     std::cout << "Exiting" << std::endl<< std::endl;
 }

 bool merkelMain::userProcessO (int userOption)
 {

     if(userOption == 0)
     {
         exit();
         return false;
     } 

     if(userOption == 1)
     {
          printHelp();
          return true;
     }
     
     if(userOption == 2)
     {
          marketStats();
          return true;

     }
     
     if(userOption == 3)
     {
          makeAnAsk();
          return true;

     }
     
     if(userOption == 4)
     {
          bid();
          return true;

     }

     if(userOption == 5)
     {
          printWallet();
          return true;

     }
     if(userOption == 6)
     {
         addToWallet();
         return true;
     }

     if(userOption == 9)
     {
          nextTimeFrame();
          return true;

     }


        invalid();
        return true;
  
 } 


