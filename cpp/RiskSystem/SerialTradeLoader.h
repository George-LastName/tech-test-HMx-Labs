#ifndef SERIALTRADELOADER_H
#define SERIALTRADELOADER_H

#include "../Models/TradeList.h"
#include "BaseLoaderTrades.h"
#include <vector>

class SerialTradeLoader : BaseLoaderTrades {
public:
    std::vector<TradeList> loadTrades();
};

#endif // SERIALTRADELOADER_H
