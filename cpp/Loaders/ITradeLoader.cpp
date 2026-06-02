#include "ITradeLoader.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


TradeList ITradeLoader::loadTrades() {
    TradeList tradeList;
    loadTradesFromFile(dataFile_, tradeList);
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
        line.erase(0, delimiter_pos+separator_.length());
    }
    items.push_back(line);
    return items;
}

void ITradeLoader::loadTradesFromFile(std::string filename, TradeList& tradeList) {
    if (filename.empty()) {
        throw std::invalid_argument("Filename cannot be null");
    }

    std::ifstream stream(filename);
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(stream, line)) {
        if (lineCount == 0) {
        } else {
            tradeList.add(createTradeFromLine(line));
        }
        lineCount++;
    }
}
