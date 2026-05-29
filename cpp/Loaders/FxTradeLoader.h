#ifndef FXTRADELOADER_H
#define FXTRADELOADER_H

#include "ITradeLoader.h"
#include "../Models/ITrade.h"
#include "../Models/TradeList.h"
#include <string>
#include <vector>
#include <memory>

class FxTradeLoader : public ITradeLoader {
private:
    static constexpr std::string separator_ = "¬";
    
    std::unique_ptr<ITrade> createTradeFromLine(std::string line);
    void loadTradesFromFile(std::string filename, TradeList& tradeList) override;
};

#endif // FXTRADELOADER_H
