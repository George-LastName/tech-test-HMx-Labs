#ifndef ITRADELOADER_H
#define ITRADELOADER_H
#include "../Models/TradeList.h"
#include "../Models/ITrade.h"
#include <vector>
#include <string>
#include <utility>

class ITradeLoader {
protected:
    std::string dataFile_;
    const char* separator_;
public:
    ITradeLoader(std::string dataFile, const char* separator) : dataFile_(std::move(dataFile)), separator_(separator) {}

    TradeList loadTrades();
    std::vector<std::string> splitLine(std::string line);

    virtual ~ITradeLoader() = default;
    virtual void loadTradesFromFile(std::string filename, TradeList& tradeList) = 0;

    virtual ITrade* createTradeFromLine(std::string line) = 0;

    virtual std::string getDataFile() const {return dataFile_;}
    virtual void setDataFile(const std::string& file) {dataFile_ = file;}
};

#endif // ITRADELOADER_H
