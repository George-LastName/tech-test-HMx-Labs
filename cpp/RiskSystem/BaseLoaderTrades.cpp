#include "BaseLoaderTrades.h"
#include "../Loaders/ITradeLoader.h"
#include "../Loaders/BondTradeLoader.h"
#include "../Loaders/FxTradeLoader.h"

#include <vector>
#include <memory>

std::vector<std::unique_ptr<ITradeLoader>> BaseLoaderTrades::getTradeLoaders(){
    std::vector<std::unique_ptr<ITradeLoader>> loaders;

    std::unique_ptr<BondTradeLoader> bondLoader = std::make_unique<BondTradeLoader>("TradeData/BondTrades.dat");
    loaders.push_back(std::move(bondLoader));

    std::unique_ptr<FxTradeLoader> fxLoader = std::make_unique<FxTradeLoader>("TradeData/FxTrades.dat");
    loaders.push_back(std::move(fxLoader));

    return loaders;
}
