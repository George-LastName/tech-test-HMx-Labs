#include "ParallelPricer.h"
#include "../Models/TradeList.h"
#include <stdexcept>

ParallelPricer::~ParallelPricer() {

}

void ParallelPricer::loadPricers() {
    PricingConfigLoader pricingConfigLoader("./PricingConfig/PricingEngines.xml");
    PricingEngineConfig pricerConfig = pricingConfigLoader.loadConfig();
    
    for (const auto& configItem : pricerConfig) {
        throw std::runtime_error("Not implemented");
    }
}

void ParallelPricer::price(const std::vector<TradeList>& tradeContainers,
                           IScalarResultReceiver* resultReceiver) {
    throw std::runtime_error("Not implemented");
}
