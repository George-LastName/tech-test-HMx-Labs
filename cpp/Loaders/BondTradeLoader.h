#ifndef BONDTRADELOADER_H
#define BONDTRADELOADER_H

#include "ITradeLoader.h"
#include "../Models/BondTrade.h"
#include "../Models/TradeList.h"
#include <string>
#include <vector>
#include <memory>

class BondTradeLoader : public ITradeLoader {
private:
    // static constexpr std::string separator_ = ",";

    BondTrade* createTradeFromLine(std::string line) override;
    void loadTradesFromFile(std::string filename, TradeList& tradeList) override;
public:
    BondTradeLoader() : ITradeLoader(",") {}
};

#endif // BONDTRADELOADER_H
