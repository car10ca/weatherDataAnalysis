#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include "weatherData.h"

#include "Period.h"

class CSVReader {
public:
    CSVReader(const std::string& filename);
    std::vector<WeatherData> readData(const std::string& country, Period period, int day, int month, int year);

private:
    std::string filename;
    std::string getTemperatureColumn(const std::string& country);
    std::string timestampToDate(const std::string& timestamp, Period period);
    bool matchPeriod(const std::tm& tm, Period period, int day, int month, int year);
};

#endif // CSVREADER_H
