#include "candlestickDataProcessor.h"
#include <limits>
#include <numeric>
#include <unordered_map>
#include <sstream>
#include <algorithm>

// function to process data for daily candlesticks
std::vector<Candlestick> CandlestickDataProcessor::processDayData(const std::vector<WeatherData>& data) {
    std::vector<Candlestick> candlesticks;
    std::unordered_map<std::string, std::vector<double>> dayData;

    // sort the data by date to ensure chronological order
    std::vector<WeatherData> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end(), [](const WeatherData& a, const WeatherData& b) {
        return a.date < b.date;
    });

    // group temperatures by day
    for (const auto& entry : sortedData) {
        std::string day = entry.date.substr(0, 10); // extract YYYY-MM-DD
        dayData[day].push_back(entry.temperature);
    }

    // create candlesticks for each day
    for (auto it = dayData.begin(); it != dayData.end(); ++it) {
        const std::string& date = it->first;
        const std::vector<double>& temps = it->second;

        double high = *std::max_element(temps.begin(), temps.end()); // get the highest temperature of the day
        double low = *std::min_element(temps.begin(), temps.end()); // get the lowest temperature of the day
        double open = temps.front(); // get the first temperature of the day
        double close = temps.back(); // get the last temperature of the day

        Candlestick candlestick(date, open, high, low, close); // create a candlestick object
        candlesticks.push_back(candlestick); // add the candlestick to the vector
    }

    // sort candlesticks by date to maintain chronological order
    std::sort(candlesticks.begin(), candlesticks.end(), [](const Candlestick& a, const Candlestick& b) {
        return a.getDate() < b.getDate();
    });

    return candlesticks;
}

// function to process data for monthly candlesticks
std::vector<Candlestick> CandlestickDataProcessor::processMonthData(const std::vector<WeatherData>& data) {
    std::vector<Candlestick> candlesticks;
    std::unordered_map<std::string, std::vector<double>> monthData;

    // sort the data by date to ensure chronological order
    std::vector<WeatherData> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end(), [](const WeatherData& a, const WeatherData& b) {
        return a.date < b.date;
    });

    // group temperatures by month
    for (const auto& entry : sortedData) {
        std::string month = entry.date.substr(0, 7); // extract YYYY-MM
        monthData[month].push_back(entry.temperature);
    }

    // create candlesticks for each month
    for (auto it = monthData.begin(); it != monthData.end(); ++it) {
        const std::string& month = it->first;
        const std::vector<double>& temps = it->second;

        double high = *std::max_element(temps.begin(), temps.end()); // get the highest temperature of the month
        double low = *std::min_element(temps.begin(), temps.end()); // get the lowest temperature of the month
        double open = temps.front(); // get the first temperature of the month
        double close = temps.back(); // get the last temperature of the month

        Candlestick candlestick(month, open, high, low, close); // create a candlestick object
        candlesticks.push_back(candlestick); // add the candlestick to the vector
    }

    // sort candlesticks by date to maintain chronological order
    std::sort(candlesticks.begin(), candlesticks.end(), [](const Candlestick& a, const Candlestick& b) {
        return a.getDate() < b.getDate();
    });

    return candlesticks;
}

// function to process data for yearly candlesticks
std::vector<Candlestick> CandlestickDataProcessor::processYearData(const std::vector<WeatherData>& data) {
    std::vector<Candlestick> candlesticks;
    std::unordered_map<std::string, std::vector<WeatherData>> yearData;

    // sort the data by date to ensure chronological order
    std::vector<WeatherData> sortedData = data;
    std::sort(sortedData.begin(), sortedData.end(), [](const WeatherData& a, const WeatherData& b) {
        return a.date < b.date;
    });

    // group temperatures by year
    for (const auto& entry : sortedData) {
        std::string year = entry.date.substr(0, 4); // extract YYYY
        yearData[year].push_back(entry);
    }

    // create candlesticks for each year
    for (auto it = yearData.begin(); it != yearData.end(); ++it) {
        const std::string& year = it->first;
        const std::vector<WeatherData>& entries = it->second;

        double high = (*std::max_element(entries.begin(), entries.end(), [](const WeatherData& a, const WeatherData& b) {
            return a.temperature < b.temperature;
        })).temperature;

        double low = (*std::min_element(entries.begin(), entries.end(), [](const WeatherData& a, const WeatherData& b) {
            return a.temperature < b.temperature;
        })).temperature;

        // expected open and close timestamps
        std::string firstDayOfYear = year + "-01-01T00:00:00Z";
        std::string lastDayOfYear = year + "-12-31T23:00:00Z";

        // find the temperature for January 1st
        double open = std::numeric_limits<double>::quiet_NaN();
        for (size_t i = 0; i < entries.size(); ++i) {
            if (entries[i].date == firstDayOfYear) {
                open = entries[i].temperature;
                break;
            }
        }

        // if January 1st is not found, use the first entry's temperature
        if (std::isnan(open)) {
            open = entries.front().temperature;
        }

        // find the temperature for December 31st
        double close = std::numeric_limits<double>::quiet_NaN();
        for (size_t i = entries.size(); i-- > 0;) {
            if (entries[i].date == lastDayOfYear) {
                close = entries[i].temperature;
                break;
            }
        }

        // if December 31st is not found, use the last entry's temperature
        if (std::isnan(close)) {
            close = entries.back().temperature;
        }

        // create candlestick for the year
        Candlestick candlestick(year, open, high, low, close); // create a candlestick object
        candlesticks.push_back(candlestick); // add the candlestick to the vector
    }

    // sort candlesticks by date to maintain chronological order
    std::sort(candlesticks.begin(), candlesticks.end(), [](const Candlestick& a, const Candlestick& b) {
        return a.getDate() < b.getDate();
    });

    return candlesticks;
}
