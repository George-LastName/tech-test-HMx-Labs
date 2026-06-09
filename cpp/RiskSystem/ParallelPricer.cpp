#include "ParallelPricer.h"
#include "../Models/TradeList.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Models/ITrade.h"
#include "../Pricers/IPricingEngine.h"

#include <vector>
#include <future>
#include <string>
#include <map>

void ParallelPricer::price(const std::vector<TradeList>& tradeContainers,
                           IScalarResultReceiver* resultReceiver) {
    loadPricers();

    std::vector<std::future<void>> results;

    for (const auto& tradeContainer : tradeContainers) {
        for (ITrade* trade : tradeContainer) {
            results.push_back(std::async(std::launch::async, [this, trade, resultReceiver]() {
                std::string tradeType = trade->getTradeType();
                if (pricers_.find(tradeType) == pricers_.end()) {
                    resultReceiver->addError(trade->getTradeId(), "No Pricing Engines available for this trade type");
                } else {
                    pricers_[tradeType].get()->price(trade, resultReceiver);
                }
            }));
        }
    }

    for (auto& result : results) result.get();
}
