#include "StreamingTradeLoader.h"

#include <stdexcept>
#include <fstream>
#include <memory>

void StreamingTradeLoader::loadAndPrice(IScalarResultReceiver* resultReceiver) {
    loadPricers();
    auto loaders = getTradeLoaders();

    for (auto& loader : loaders){
        std::string filename = loader->getDataFile();
        if (filename.empty()) {
            throw std::invalid_argument("Filename cannot be null");
        }

        std::ifstream stream(filename);
        if (!stream.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        std::string line;
        while (std::getline(stream, line)) {
            if (line.find("Type") != std::string::npos || line.find("FxTrades") != std::string::npos || line.find("END") != std::string::npos) {
                continue;
            } else {
                auto trade = loader->createTradeFromLine(line);
                std::string tradeType = trade->getTradeType();
                if (pricers_.find(tradeType) == pricers_.end()) {
                    resultReceiver->addError(trade->getTradeId(), "No Pricing Engines available for this trade type");
                    continue;
                }
                pricers_[tradeType]->price(trade, resultReceiver);
            }
        }
    }
}
