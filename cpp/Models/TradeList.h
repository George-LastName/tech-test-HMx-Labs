#ifndef TRADELIST_H
#define TRADELIST_H

#include "ITrade.h"
#include "ITradeReceiver.h"
#include <vector>

class TradeList : public ITradeReceiver {
public:
    TradeList() = default;

    ~TradeList(){
        for (auto trade : trades_){
            delete trade;
        }
    }

    // copy constructor
    TradeList(const TradeList& other){
        for(auto trade : other){
            add(trade->clone());
        }
    }

    // move constructor
    TradeList(TradeList&& other) noexcept {
        trades_ = std::move(other.trades_);
    }

    // copy assignment
    TradeList& operator=(const TradeList& other){
        TradeList tmp(other);
        std::swap(trades_, tmp.trades_);
        return *this;
    }

    // move assignment
    TradeList& operator=(TradeList&& other) noexcept {
        for (auto trade : trades_){
            delete trade;
        }
        trades_ = std::move(other.trades_);
        return *this;
    }

    void add(ITrade* trade) override {
        trades_.push_back(trade);
    }
    
    size_t size() const { return trades_.size(); }
    ITrade* operator[](size_t index) const { return trades_[index]; }
    
    using iterator = std::vector<ITrade*>::iterator;
    using const_iterator = std::vector<ITrade*>::const_iterator;
    
    iterator begin() { return trades_.begin(); }
    iterator end() { return trades_.end(); }
    const_iterator begin() const { return trades_.begin(); }
    const_iterator end() const { return trades_.end(); }

    std::vector<ITrade*>* getTrades() { return &trades_;}
    
private:
    std::vector<ITrade*> trades_;
};

#endif // TRADELIST_H
