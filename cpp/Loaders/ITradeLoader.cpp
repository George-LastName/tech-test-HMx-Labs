#include "ITradeLoader.h"


TradeList ITradeLoader::loadTrades() {
    TradeList tradeList;
    loadTradesFromFile(dataFile_, tradeList);
    return tradeList;
}
