# MerkelMain C++ OOP APP

**Crypto exchange simulation app**

This project, is an app that simulating crypto exchange based on orderbook (csv data) and user input.

The app read data from csv file, each row is an ask/bid on the order book.

example: 2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187305,6.85567013

This row means: a bid to buy ETH, willing to pay 0.02 BTC for each unit. Max ammount willing to buy is 6.85 ETH.


**App flow**

The user must insert money into his wallet to place an ask/bid on the orderbook.

then the user can place an ask/bid offer.

The app check if the user wallet contain enough currencies to place the offer.

When pressing 9 (countinue) in the menu, the app move to next timestamp - and match ask to bid if there are possible matches.

The app have 10 timestamps, and it reset every time it reach to the end (OrderBook::getNextTime).

**Menu options**
1. print help - basic help for the user to understand how the app works.
2. print exchange stats - provide data of the highest bid and lowest ask for each product in the order book.
3. Make an ask - insert an user ask into the orderbook.
4. Make a bid - insert an user bid into the orderbook.
5. Print wallet - print user wallet content.
6. Add to wallet - insert currencies into wallet
9. Continue - move to the next timestamp
0. Exit - exit from the app

**Classes**
1. CSVReader - transform csv data/user input into an OrderBookEntry object.
2. OrderBookEntry  - Represnt an object in our orderbook, each object is an offer (bid or ask).
3. OrderBook - contain all orderBookEntry objects as an orderbook.
4. Wallet - the user wallet.
5. MerkelMain - the whole app, all user interface and app functions.

**App functionalities**
1. OOP based project, main used only to init the app.
2. Read,tokenise and validate data received from csv file/user input.
3. Create and implement logic to match asks to bids (OrderBook::matchAskToBid)





