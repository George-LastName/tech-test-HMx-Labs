#ifndef SERIALTRADELOADER_H
#define SERIALTRADELOADER_H

#include "../Loaders/ITradeLoader.h"
#include "../Models/TradeList.h"
#include <vector>
#include <memory>

class SerialTradeLoader {
private:
    std::vector<std::unique_ptr<ITradeLoader>> getTradeLoaders();
    
public:
    std::vector<TradeList> loadTrades();
};

#endif // SERIALTRADELOADER_H
