#ifndef CSV_READER_PREDICTION_H
#define CSV_READER_PREDICTION_H

#include <string>
#include <vector>

class CSVReaderPrediction {
public:
    CSVReaderPrediction(const std::string& fileName);
    std::vector<std::pair<std::string, double>> getCountryTemperatureData(const std::string& country);

private:
    std::string fileName;
};

#endif // CSV_READER_PREDICTION_H
