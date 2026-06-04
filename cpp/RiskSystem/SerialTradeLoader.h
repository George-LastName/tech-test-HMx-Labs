#ifndef SERIALTRADELOADER_H
#define SERIALTRADELOADER_H

#include "../Loaders/ITradeLoader.h"
#include "../Models/TradeList.h"
#include "BaseLoaderTrades.h"
#include <vector>
#include <memory>

class SerialTradeLoader : BaseLoaderTrades {
public:
    std::vector<TradeList> loadTrades();
};

#endif // SERIALTRADELOADER_H
