#ifndef BONDTRADE_H
#define BONDTRADE_H

#include "BaseTrade.h"

class BondTrade : public BaseTrade {
public:
    static constexpr const char* GovBondTradeType = "GovBond";
    static constexpr const char* CorpBondTradeType = "CorpBond";
    
    BondTrade(const std::string& tradeId, const std::string& tradeType = GovBondTradeType)
        : BaseTrade(tradeId, tradeType) {}

    BondTrade* clone() const override {
        return new BondTrade(*this);
    }
};

#endif // BONDTRADE_H

