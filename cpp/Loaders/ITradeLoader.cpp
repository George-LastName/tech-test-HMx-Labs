#include "ITradeLoader.h"


std::vector<ITrade*> ITradeLoader::loadTrades() {
    TradeList tradeList;
    loadTradesFromFile(dataFile_, tradeList);

    std::vector<ITrade*> result;
    for (size_t i = 0; i < tradeList.size(); ++i) {
        result.push_back(tradeList[i]);
    }
    return result;
}
