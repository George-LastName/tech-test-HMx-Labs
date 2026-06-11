#ifndef BONDTRADELOADER_H
#define BONDTRADELOADER_H

#include "ITradeLoader.h"
#include "../Models/BondTrade.h"
#include <string>
#include <utility>

class BondTradeLoader : public ITradeLoader {
private:
    BondTrade* createTradeFromLine(std::string line) override;
    void loadTradesFromFile(TradeList& tradeList) override;
public:
    BondTradeLoader(std::string dataFile) : ITradeLoader(std::move(dataFile), ",") {}
};

#endif // BONDTRADELOADER_H
