#ifndef SERIALPRICER_H
#define SERIALPRICER_H

#include "../Models/IPricingEngine.h"
#include "../Models/TradeList.h"
#include "../Models/IScalarResultReceiver.h"
#include "BasePricer.h"
#include "PricingConfigLoader.h"

#include <vector>

class SerialPricer : BasePricer {
public:
    ~SerialPricer() = default;
    void price(const std::vector<TradeList>& tradeContainers,
               IScalarResultReceiver* resultReceiver);
};

#endif // SERIALPRICER_H
