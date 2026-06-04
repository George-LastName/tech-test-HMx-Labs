#ifndef BASEPRICINGENGINE_H
#define BASEPRICINGENGINE_H

#include "IPricingEngine.h"
#include "../Models/ITrade.h"
#include "../Models/IScalarResultReceiver.h"
#include <map>
#include <string>
#include <random>
#include <mutex>

class BasePricingEngine : public IPricingEngine {
private:
    std::map<std::string, unsigned int> supportedTypes_;
    int delay_;
    
    class Random {
    public:
        Random();
        double nextDouble();
    private:
        std::mutex mutex_;
        std::random_device rd_;
        std::mt19937 gen_;
        std::uniform_int_distribution<unsigned int> dist_;
    };

    Random random_;
    
    static std::map<std::string, std::string>& getTradesToError();
    static std::map<std::string, std::string>& getTradesToWarn();

protected:
    BasePricingEngine();
    ~BasePricingEngine() override = default;

    void price(ITrade* trade, IScalarResultReceiver* resultReceiver) override;
    void addSupportedTradeType(const std::string& tradeType);
    int getDelay() const;
    void setDelay(int delay);
    virtual void priceTrade(ITrade* trade, IScalarResultReceiver* resultReceiver);
    virtual double calculateResult();

public:
    bool isTradeTypeSupported(const std::string& tradeType) const;

};

#endif // BASEPRICINGENGINE_H
