#include "SerialPricer.h"
#include "../Models/ITrade.h"
#include "../Models/TradeList.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Pricers/IPricingEngine.h"

#include <vector>
#include <string>


void SerialPricer::price(const std::vector<TradeList>& tradeContainers,
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
