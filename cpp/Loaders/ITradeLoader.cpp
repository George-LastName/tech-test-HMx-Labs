#include "ITradeLoader.h"
#include "../Models/TradeList.h"

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstring>


TradeList ITradeLoader::loadTrades() {
    TradeList tradeList;
    loadTradesFromFile(tradeList);
    return tradeList;
}

std::vector<std::string> ITradeLoader::splitLine(std::string line){
    std::vector<std::string> items;
    std::string item;

    // Remove whitespace characters e.g. \n, \t, \r
    line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char x) {return std::isspace(x);}), line.end());

    size_t delimiter_pos = 0;
    while((delimiter_pos = line.find(separator_)) != std::string::npos){
        item = line.substr(0, delimiter_pos);
        items.push_back(item);
        line.erase(0, delimiter_pos+strlen(separator_));
    }
    items.push_back(line);
    return items;
}
