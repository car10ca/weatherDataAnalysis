#include "CSVReaderPrediction.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

// constructor initializes the csv reader with the file name
CSVReaderPrediction::CSVReaderPrediction(const std::string& fileName) : fileName(fileName) {}

// function to get temperature data for a specific country from the csv file
std::vector<std::pair<std::string, double>> CSVReaderPrediction::getCountryTemperatureData(const std::string& country) {
    std::vector<std::pair<std::string, double>> data;  // vector to store the parsed data
    std::ifstream file(fileName);  // open the csv file
    std::string line, timestamp, tempStr;
    bool isFirstLine = true;  // flag to check if the current line is the header line
    int countryIndex = -1;  // index of the country's temperature column
    std::string countryHeader = country + "_temperature";  // construct the header name for the country's temperature

    // check if the file is open
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return data;  // return empty data if file cannot be opened
    }

    // read the file line by line
    while (getline(file, line)) {
        std::stringstream ss(line);  // create a stringstream from the line
        if (isFirstLine) {
            isFirstLine = false;  // set flag to false after processing the header line
            std::string header;
            int index = 0;
            // read the headers and find the index of the relevant country temperature column
            while (getline(ss, header, ',')) {
                if (header == countryHeader) {
                    countryIndex = index;
                    break;
                }
                index++;
            }
            // check if the relevant header was found
            if (countryIndex == -1) {
                std::cerr << "Country not found in CSV headers: " << countryHeader << std::endl;
                return data;  // exit if no relevant header is found
            }
        } else {
            std::getline(ss, timestamp, ',');  // read the timestamp
            std::vector<std::string> rowValues;  // vector to store the row values
            // read the values in the row
            while (getline(ss, tempStr, ',')) {
                rowValues.push_back(tempStr);
            }
            // check if the country index is within the range of the row values
            if (countryIndex < rowValues.size()) {
                try {
                    double temp = std::stod(rowValues[countryIndex]);  // convert the temperature string to double
                    data.emplace_back(timestamp, temp);  // add the timestamp and temperature to the data vector
                } catch (const std::exception& e) {
                    std::cerr << "Failed to convert temperature: " << tempStr << " Error: " << e.what() << std::endl;
                }
            }
        }
    }

    file.close();  // close the file
    return data;  // return the parsed data
}
