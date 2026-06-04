#ifndef BASELOADERTRADES_H
#define BASELOADERTRADES_H

#include <vector>
#include <memory>

#include "../Loaders/ITradeLoader.h"


class BaseLoaderTrades {
public:
    std::vector<std::unique_ptr<ITradeLoader>> getTradeLoaders();
};

#endif // BASELOADERTRADES_H
