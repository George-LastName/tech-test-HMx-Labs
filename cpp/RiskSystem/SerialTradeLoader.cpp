#include "SerialTradeLoader.h"

#include "../Models/TradeList.h"
#include "../Loaders/ITradeLoader.h"
#include <vector>
#include <memory>


std::vector<TradeList> SerialTradeLoader::loadTrades() {
    auto loaders = getTradeLoaders();
    std::vector<TradeList> result;
    
    for (auto& loader : loaders) {
        result.push_back(loader->loadTrades());
    }
    
    return result;
}

