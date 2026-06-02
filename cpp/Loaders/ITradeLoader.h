#ifndef ITRADELOADER_H
#define ITRADELOADER_H

#include "../Models/ITrade.h"
#include "../Models/TradeList.h"
#include <vector>
#include <string>

class ITradeLoader {
protected:
    std::string dataFile_;
public:
    virtual ~ITradeLoader() = default;
    virtual TradeList loadTrades();
    virtual void loadTradesFromFile(std::string filename, TradeList& tradeList) = 0;

    virtual std::string getDataFile() const {return dataFile_;}
    virtual void setDataFile(const std::string& file) {dataFile_ = file;}
};

#endif // ITRADELOADER_H
