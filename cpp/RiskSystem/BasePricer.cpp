#include "BasePricer.h"

#include "../Pricers/GovBondPricingEngine.h"
#include "../Pricers/CorpBondPricingEngine.h"
#include "../Pricers/FxPricingEngine.h"
#include "PricingConfigLoader.h"
#include "PricingEngineConfig.h"
#include "PricingEngineConfigItem.h"

#include <iostream>
#include <memory>
#include <stdexcept>

void BasePricer::loadPricers() {
    PricingConfigLoader pricingConfigLoader("./PricingConfig/PricingEngines.xml");
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
