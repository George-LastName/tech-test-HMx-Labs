#ifndef STREAMINGTRADELOADER_H
#define STREAMINGTRADELOADER_H

#include "../Models/IScalarResultReceiver.h"
#include "BaseLoaderTrades.h"
#include "BasePricer.h"


class StreamingTradeLoader : BaseLoaderTrades, BasePricer {
public:
    ~StreamingTradeLoader() = default;
    
    void loadAndPrice(IScalarResultReceiver* resultReceiver);
};

#endif // STREAMINGTRADELOADER_H
