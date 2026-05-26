#include "SerialPricer.h"
#include <stdexcept>
#include <iostream>
#include <memory>

#include "../Pricers/GovBondPricingEngine.h"
#include "../Pricers/CorpBondPricingEngine.h"
#include "../Pricers/FxPricingEngine.h"

SerialPricer::~SerialPricer() {

}

void SerialPricer::loadPricers() {
    PricingConfigLoader pricingConfigLoader;
    pricingConfigLoader.setConfigFile("./PricingConfig/PricingEngines.xml");
    PricingEngineConfig pricerConfig = pricingConfigLoader.loadConfig();

    for (const auto& configItem : pricerConfig) {
        std::cout << configItem.getTradeType() << "\n";
        std::string type = configItem.getTradeType();
        if(type == "GovBond"){
            pricers_[type] = std::make_unique<GovBondPricingEngine>();
        } else if (type == "CorpBond"){
            pricers_[type] = std::make_unique<CorpBondPricingEngine>();
        } else if (type == "FxSpot" || type == "FxFwd"){
            pricers_[type] = std::make_unique<FxPricingEngine>();
        } else {
            throw std::runtime_error("Unknown engine type in loaded xml file.");
        }
    }
}

void SerialPricer::price(const std::vector<std::vector<ITrade*>>& tradeContainers, 
                         IScalarResultReceiver* resultReceiver) {
    loadPricers();
    
    for (const auto& tradeContainer : tradeContainers) {
        for (ITrade* trade : tradeContainer) {
            std::string tradeType = trade->getTradeType();
            if (pricers_.find(tradeType) == pricers_.end()) {
                resultReceiver->addError(trade->getTradeId(), "No Pricing Engines available for this trade type");
                continue;
            }
            
            IPricingEngine* pricer = pricers_[tradeType].get();
            pricer->price(trade, resultReceiver);
        }
    }
}
