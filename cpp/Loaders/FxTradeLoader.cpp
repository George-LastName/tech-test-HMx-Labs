#include "FxTradeLoader.h"
#include "../Models/FxTrade.h"
#include "../Models/TradeList.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <string>
#include <vector>

FxTrade* FxTradeLoader::createTradeFromLine(std::string line) {
    auto items = splitLine(line);

    if (items.size() < 9) {
        throw std::runtime_error("Invalid line format");
    }
    FxTrade* trade = new FxTrade(items[8], items[0]);

    std::tm tm = {};
    std::istringstream dateStream(items[1]);
    dateStream >> std::get_time(&tm, "%Y-%m-%d");
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    trade->setTradeDate(timePoint);
    std::istringstream dateStream2(items[6]);
    dateStream2 >> std::get_time(&tm, "%Y-%m-%d");
    auto timePoint2 = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    trade->setValueDate(timePoint2);

    trade->setInstrument(items[2]+items[3]);
    trade->setCounterparty(items[7]);
    trade->setNotional(std::stod(items[4]));
    trade->setRate(std::stod(items[5]));

    return trade;
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
