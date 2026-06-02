#ifndef ITRADELOADER_H
#define ITRADELOADER_H

#include "../Models/ITrade.h"
#include "../Models/TradeList.h"
#include <vector>
#include <string>

class ITradeLoader {
protected:
    std::string dataFile_;
    std::string separator_;
public:
    // ITradeLoader() = default;
    ITradeLoader(std::string separator) : separator_(separator) {}
    virtual ~ITradeLoader() = default;
    virtual TradeList loadTrades();
    virtual void loadTradesFromFile(std::string filename, TradeList& tradeList) = 0;

    virtual ITrade* createTradeFromLine(std::string line) = 0;
    std::vector<std::string> splitLine(std::string line);

    virtual std::string getDataFile() const {return dataFile_;}
    virtual void setDataFile(const std::string& file) {dataFile_ = file;}
};

#endif // ITRADELOADER_H
