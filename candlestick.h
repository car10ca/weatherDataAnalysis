#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include <string>
#include <iostream>

class Candlestick {
public:
    Candlestick(const std::string& date, double open, double high, double low, double close);
    void display() const;
    std::string getDate() const; // Getter for date
    double getOpen() const;      // Getter for open
    double getHigh() const;      // Getter for high
    double getLow() const;       // Getter for low
    double getClose() const;     // Getter for close

private:
    std::string date;
    double open;
    double high;
    double low;
    double close;
};

#endif // CANDLESTICK_H
