#include "Wallet.h"
#include <iostream>


        Wallet::Wallet ()
        {
            
        }
        // insert money into wallet
        void Wallet::insertMoney (std::string type , double ammount)
        {   
            if (ammount < 0)
            {
                std::cout<< "Wallet::InsertMoney Negative numbr, IGNORE" << std::endl;
                return;
            }
            
            double balance;
            if (currencies.count(type) == 0)
                balance = 0;
            else
                balance = currencies[type];
            
            currencies[type] = balance+ammount;

        }

        // REMOVE money FROM wallet
        bool Wallet::RemoveMoney (std::string type , double ammount)
        {
            if (currencies.count(type) == 0 )
            {
                std::cout<< "Wallet::RemoveMoney Unknown product" << std::endl;
                return false;    
            }

            if (ammount < 0)
            {
                std::cout<< "Wallet::RemoveMoney Negative numbr, IGNORE" << std::endl;
                return false;
            }

            if (currencies[type] - ammount >= 0)
            {
                std::cout<< "Account charged in " << ammount << " " << type << std::endl;
                currencies[type] -= ammount;
                return true;
            }
             
            return false;
        }

        //check if the wallet has enough ammount of the currency to buy/sell
        bool Wallet::currencyAmmountCheck (std::string type , double ammount)
        {
            if (currencies.count(type) == 0 || currencies[type] < ammount)
            {
                std::cout << "Wallet has " << currencies[type] << " " << type <<std::endl;
                std::cout << "Please add at least "  << ammount - currencies[type] << " " << type <<std::endl;
                return false;
            }
            return true;
        }

        // print wallet content
        std::string Wallet::printWallet ()
        {
            bool emptyWallet = true;
            std::string row;
            for (std::pair<std::string,double> currnecy : currencies)
            {
                emptyWallet = false;
                std::string type = currnecy.first;
                double ammount = currnecy.second;
                row += type + " : " + std::to_string(ammount) + "\n";
            }

            if (emptyWallet)
                return "Wallet is empty";

            return row;
           
        }


