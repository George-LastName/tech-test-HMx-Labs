#include "ScreenResultPrinter.h"
#include "../Models/ScalarResults.h"
#include <iostream>
#include <string>
#include <optional>

void ScreenResultPrinter::printResults(ScalarResults& results) {
    for (const auto& result : results) {
        std::string tradeId = result.getTradeId();
        std::optional<double> res = result.getResult();
        std::optional<std::string> err = result.getError();

        std::cout << tradeId;
        if(res){
            std::cout << " : " << res.value();
        }
        if (err){
            std::cout << " : " << err.value();
        }
        std::cout << std::endl;
    }
}
