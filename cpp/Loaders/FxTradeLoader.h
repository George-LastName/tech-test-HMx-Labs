#ifndef FXTRADELOADER_H
#define FXTRADELOADER_H

#include "ITradeLoader.h"
#include "../Models/FxTrade.h"
#include "../Models/TradeList.h"
#include <string>
#include <vector>

class FxTradeLoader : public ITradeLoader {
private:
    // static constexpr std::string separator_ = "¬";

    FxTrade* createTradeFromLine(std::string line) override;
    void loadTradesFromFile(std::string filename, TradeList& tradeList) override;
public:
    FxTradeLoader(std::string dataFile) : ITradeLoader(dataFile, "¬") {}

};

#endif // FXTRADELOADER_H
