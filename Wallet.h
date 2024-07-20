#include <string>
#include <map>

//user Wallet
class Wallet 
{
    public:
        Wallet ();
        // insert money into wallet
        void insertMoney (std::string type , double ammount);

         // REMOVE money FROM wallet
        bool RemoveMoney (std::string type , double ammount);

        //check if the wallet has enough ammount of the currency to buy/sell
        bool currencyAmmountCheck (std::string type , double ammount);

        // print wallet content
        std::string printWallet ();
        
    private:
        //contains wallet content
        std::map <std::string, double> currencies;
};