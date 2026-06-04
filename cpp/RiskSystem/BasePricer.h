#ifndef BASEPRICER_H
#define BASEPRICER_H

#include "../Pricers/IPricingEngine.h"

#include <memory>
#include <map>
#include <string>

class BasePricer{
protected:
    std::map<std::string, std::unique_ptr<IPricingEngine>> pricers_;
public:
    void loadPricers();
};


#endif // BASEPRICER_H
