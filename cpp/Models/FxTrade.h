#ifndef FXTRADE_H
#define FXTRADE_H

#include "BaseTrade.h"
#include <chrono>

class FxTrade : public BaseTrade {
public:
    static constexpr const char* FxSpotTradeType = "FxSpot";
    static constexpr const char* FxForwardTradeType = "FxFwd";
    
    FxTrade(const std::string& tradeId, const std::string& tradeType = FxSpotTradeType)
        : BaseTrade(tradeId, tradeType) {}

    FxTrade* clone() const override {
        return new FxTrade(*this);
    }
    
    std::chrono::system_clock::time_point getValueDate() const { return valueDate_; }
    void setValueDate(const std::chrono::system_clock::time_point& date) { valueDate_ = date; }
    
private:
    std::chrono::system_clock::time_point valueDate_;
};

#endif // FXTRADE_H

