#include "candlestick.h"

// constructor to initialize a candlestick object with the given date, open, high, low, and close temperatures
Candlestick::Candlestick(const std::string& date, double open, double high, double low, double close)
    : date(date), open(open), high(high), low(low), close(close) {}

// method to display the candlestick data
void Candlestick::display() const {
    std::cout << "Date: " << date
              << " Open: " << open
              << " High: " << high
              << " Low: " << low
              << " Close: " << close << std::endl;
}

// method to get the date of the candlestick
std::string Candlestick::getDate() const {
    return date;
}

// method to get the open temperature of the candlestick
double Candlestick::getOpen() const {
    return open;
}

// method to get the high temperature of the candlestick
double Candlestick::getHigh() const {
    return high;
}

// method to get the low temperature of the candlestick
double Candlestick::getLow() const {
    return low;
}

// method to get the close temperature of the candlestick
double Candlestick::getClose() const {
    return close;
}
