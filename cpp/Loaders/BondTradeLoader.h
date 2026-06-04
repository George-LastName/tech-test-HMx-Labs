#ifndef BONDTRADELOADER_H
#define BONDTRADELOADER_H

#include "ITradeLoader.h"
#include "../Models/BondTrade.h"
#include "../Models/TradeList.h"
#include <string>

class BondTradeLoader : public ITradeLoader {
private:
    BondTrade* createTradeFromLine(std::string line) override;
    void loadTradesFromFile(std::string filename, TradeList& tradeList) override;
public:
    BondTradeLoader(std::string dataFile) : ITradeLoader(std::move(dataFile), ",") {}
};

#endif // BONDTRADELOADER_H
