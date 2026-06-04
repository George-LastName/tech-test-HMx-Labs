#ifndef BASETRADE_H
#define BASETRADE_H

#include "ITrade.h"
#include <chrono>
#include <string>
#include <assert.h>

class BaseTrade : public ITrade {
public:
    // BaseTrade() = default;
    BaseTrade(const std::string& tradeId, const std::string& tradeType) {
    // : tradeId_(std::move(tradeId)), tradeType_(std::move(tradeType)) {
        if (tradeId.empty()) {
            throw std::invalid_argument("A valid non null, non empty trade ID must be provided.");
        }
        if (tradeType.empty()){
            throw std::invalid_argument("A valid non null, non empty trade Type must be provided.");
        }

        tradeId_ = tradeId;
        tradeType_ = tradeType;
    }
    ~BaseTrade() override = default;
    ITrade* clone() const override = 0;
    
    std::chrono::system_clock::time_point getTradeDate() const override { return tradeDate_; }
    void setTradeDate(const std::chrono::system_clock::time_point& date) override { tradeDate_ = date; }

    std::string getInstrument() const override { return instrument_; }
    void setInstrument(const std::string& instrument) override { instrument_ = instrument; }
    
    std::string getCounterparty() const override { return counterparty_; }
    void setCounterparty(const std::string& counterparty) override { counterparty_ = counterparty; }
    
    double getNotional() const override { return notional_; }
    void setNotional(double notional) override { notional_ = notional; }
    
    double getRate() const override { return rate_; }
    void setRate(double rate) override { rate_ = rate; }
    
    std::string getTradeType() const override { return tradeType_; }
    std::string getTradeId() const override { return tradeId_; }

protected:
    std::string tradeId_;
    std::string tradeType_;
    
private:
    std::chrono::system_clock::time_point tradeDate_;
    std::string instrument_;
    std::string counterparty_;
    double notional_ = 0.0;
    double rate_ = 0.0;
};

#endif // BASETRADE_H

