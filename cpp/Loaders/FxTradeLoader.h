#ifndef FXTRADELOADER_H
#define FXTRADELOADER_H
#include "ITradeLoader.h"
#include "../Models/FxTrade.h"
#include <utility>
#include <string>

class FxTradeLoader : public ITradeLoader {
private:
    FxTrade* createTradeFromLine(std::string line) override;
    void loadTradesFromFile(std::string filename, TradeList& tradeList) override;
public:
    FxTradeLoader(std::string dataFile) : ITradeLoader(std::move(dataFile), "¬") {}

};

#endif // FXTRADELOADER_H
