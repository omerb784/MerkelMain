#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class merkelMain {

    public:

    merkelMain ();
    void init ();

    private:

    void printMenu();
    int getUserOption ();
    void invalid ();
    void printHelp ();
    void marketStats ();
    void makeAnAsk ();
    void bid ();
    void printWallet ();
    void addToWallet ();
    void nextTimeFrame ();
    bool userProcessO (int userOption);
    void exit ();
    

    OrderBook orderBook{};
    std::string currnetTime;
    Wallet Wallet {};

};