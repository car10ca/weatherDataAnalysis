#include "candlestickPlotter.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void CandlestickPlotter::plotCandlesticks(const std::vector<Candlestick>& candlesticks) {
    if (candlesticks.empty()) {
        std::cout << "No data available to plot" << std::endl;
        return;
    }

    // determine the min and max temperatures for scaling
    double minTemp = std::numeric_limits<double>::max();
    double maxTemp = std::numeric_limits<double>::min();

    // find the min and max temperatures across all candlesticks
    for (const auto& c : candlesticks) {
        minTemp = std::min({minTemp, c.getLow(), c.getOpen(), c.getClose(), c.getHigh()});
        maxTemp = std::max({maxTemp, c.getLow(), c.getOpen(), c.getClose(), c.getHigh()});
    }

    const int plotWidth = 50;  // width of the plot line

    // lambda function to scale a temperature value to the plot width
    auto scaleTemp = [minTemp, maxTemp, plotWidth](double temp) {
        return static_cast<int>(((temp - minTemp) / (maxTemp - minTemp)) * (plotWidth - 1));
    };

    // print each candlestick with the corresponding text-based plot
    for (const auto& c : candlesticks) {
        std::cout << "Date: " << c.getDate() << " | ";

        // calculate positions on the plot line for open, close, high, and low temperatures
        int openPos = scaleTemp(c.getOpen());
        int closePos = scaleTemp(c.getClose());
        int highPos = scaleTemp(c.getHigh());
        int lowPos = scaleTemp(c.getLow());

        // create the plot line filled with spaces
        std::string plotLine(plotWidth, ' ');

        // draw the high-low line
        for (int j = lowPos; j <= highPos; ++j) {
            plotLine[j] = '-';
        }

        // mark the open and close positions
        plotLine[openPos] = '|';
        plotLine[closePos] = '|';

        // print the plot line with temperatures
        std::cout << plotLine << " | Open: " << c.getOpen()
                  << " High: " << c.getHigh()
                  << " Low: " << c.getLow()
                  << " Close: " << c.getClose() << std::endl;
    }

    // print the temperature range
    std::cout << "Temperature range: " << minTemp << " to " << maxTemp << " degrees" << std::endl;
}
