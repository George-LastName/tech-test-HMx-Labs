#include "../Models/ScalarResults.h"
#include "../Models/TradeList.h"
#include "../RiskSystem/SerialTradeLoader.h"
#include "../RiskSystem/StreamingTradeLoader.h"
#include "../RiskSystem/ParallelPricer.h"
#include "../RiskSystem/ScreenResultPrinter.h"
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <cstdio>
// NOLINTNEXTLINE
int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

int main() {
    StreamingTradeLoader streamingLoader;
    ScalarResults streamingResults;
    std::cout << "Streaming Loader Start\n";
    streamingLoader.loadAndPrice(&streamingResults);


    SerialTradeLoader tradeLoader;
    std::cout << "Serial Loader Start\n";
    std::vector<TradeList> allTrades = tradeLoader.loadTrades();

    ScalarResults parallelResults;
    ParallelPricer parallelPricer;
    std::cout << "Parallel Pricer Start\n";
    parallelPricer.price(allTrades, &parallelResults);

    ScreenResultPrinter screenPrinter;
    std::cout << "Streaming Results\n";
    screenPrinter.printResults(streamingResults);
    std::cout << "------------------\nParallel Results\n";
    screenPrinter.printResults(parallelResults);
    
    std::cout << "Press any key to exit.." << std::endl;
    _getch();
    
    return 0;
}
