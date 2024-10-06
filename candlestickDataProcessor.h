#ifndef CANDLESTICKDATAPROCESSOR_H
#define CANDLESTICKDATAPROCESSOR_H

#include "weatherData.h"
#include "candlestick.h"
#include <vector>
#include <map>

class CandlestickDataProcessor {
public:
    std::vector<Candlestick> processDayData(const std::vector<WeatherData>& data);
    std::vector<Candlestick> processMonthData(const std::vector<WeatherData>& data);
    std::vector<Candlestick> processYearData(const std::vector<WeatherData>& data);
};

#endif // CANDLESTICKDATAPROCESSOR_H
