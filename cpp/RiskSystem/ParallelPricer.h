#ifndef PARALLELPRICER_H
#define PARALLELPRICER_H

#include "../Models/TradeList.h"
#include "../Models/IScalarResultReceiver.h"
#include "BasePricer.h"
#include <vector>
#include <mutex>

class ParallelPricer : BasePricer {
private:
    std::mutex resultMutex_;
public:
    ~ParallelPricer() = default;
    
    void price(const std::vector<TradeList>& tradeContainers,
               IScalarResultReceiver* resultReceiver);
};

#endif // PARALLELPRICER_H
