#include "FxTradeLoader.h"
#include "../Models/FxTrade.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <memory>

std::unique_ptr<ITrade> FxTradeLoader::createTradeFromLine(std::string line) {
    std::vector<std::string> items;
    std::string item;

    size_t delimiter_pos = 0;
    line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char x) {return std::isspace(x);}), line.end());
    while((delimiter_pos = line.find(separator_)) != std::string::npos){
        item = line.substr(0, delimiter_pos);
        items.push_back(item);
        line.erase(0, delimiter_pos+separator_.length());
    }
    items.push_back(line);

    if (items.size() < 9) {
        throw std::runtime_error("Invalid line format");
    }
    FxTrade trade = FxTrade(items[8], items[0]);

    std::tm tm = {};
    std::istringstream dateStream(items[1]);
    dateStream >> std::get_time(&tm, "%Y-%m-%d");
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    trade.setTradeDate(timePoint);
    std::istringstream dateStream2(items[6]);
    dateStream2 >> std::get_time(&tm, "%Y-%m-%d");
    auto timePoint2 = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    trade.setValueDate(timePoint2);

    trade.setInstrument(items[2]+items[3]);
    trade.setCounterparty(items[7]);
    trade.setNotional(std::stod(items[4]));
    trade.setRate(std::stod(items[5]));

    return std::make_unique<FxTrade>(trade);
}

void FxTradeLoader::loadTradesFromFile(std::string filename, TradeList& tradeList) {
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
        if (lineCount <= 1 || lineCount > 5) {
        } else {
            tradeList.add(createTradeFromLine(line));
        }
        lineCount++;
    }
}
