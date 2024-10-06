#ifndef CANDLESTICK_PLOTTER_H
#define CANDLESTICK_PLOTTER_H

#include "candlestick.h"
#include <vector>

class CandlestickPlotter {
public:
    void plotCandlesticks(const std::vector<Candlestick>& candlesticks);
};

#endif // CANDLESTICK_PLOTTER_H
