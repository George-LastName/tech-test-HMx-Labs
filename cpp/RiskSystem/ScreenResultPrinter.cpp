#include "ScreenResultPrinter.h"
#include <iostream>

void ScreenResultPrinter::printResults(ScalarResults& results) {
    for (const auto& result : results) {
        std::string tradeId = result.getTradeId();
        std::optional<double> res = result.getResult();
        std::optional<std::string> err = result.getError();
        // Write code here to print out the results such that we have:
        // TradeID : Result : Error
        std::cout << tradeId;
        if(res){
            std::cout << " : " << res.value();
        }
        if (err){
            std::cout << " : " << err.value();
        }
        std::cout << std::endl;
        // If there is no result then the output should be:
        // TradeID : Error
        // If there is no error the output should be:
        // TradeID : Result
    }
}
