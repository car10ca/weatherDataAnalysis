#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <unordered_map>

// converts a string representation of a period to the corresponding Period enum value
Period stringToPeriod(const std::string& periodStr) {
    // check if the period string is "Day" and return the corresponding enum value
    if (periodStr == "Day") return Period::Day;
    // check if the period string is "Month" and return the corresponding enum value
    else if (periodStr == "Month") return Period::Month;
    // check if the period string is "Year" and return the corresponding enum value
    else if (periodStr == "Year") return Period::Year;
    // if the period string is invalid, throw an exception
    throw std::runtime_error("Invalid period string: " + periodStr);
}

// constructor initializes the CSVReader with the filename of the CSV file to be read
CSVReader::CSVReader(const std::string& filename) : filename(filename) {}

// returns the temperature column name corresponding to the selected country
std::string CSVReader::getTemperatureColumn(const std::string& country) {
    // create a map of country names to their corresponding temperature column names
    std::unordered_map<std::string, std::string> countryToColumn = {
        {"AT - Austria", "AT_temperature"}, {"BE - Belgium", "BE_temperature"}, {"BG - Bulgaria", "BG_temperature"}, 
        {"CH - Switzerland", "CH_temperature"},
        {"CZ - Czech Republic", "CZ_temperature"}, {"DE - Germany", "DE_temperature"}, {"DK - Denmark", "DK_temperature"},
        {"EE - Estonia", "EE_temperature"}, {"ES - Spain", "ES_temperature"}, {"FI - Finland", "FI_temperature"},
        {"FR - France", "FR_temperature"}, {"GB - Great Britain", "GB_temperature"}, {"GR - Greece", "GR_temperature"},
        {"HR - Croatia", "HR_temperature"}, {"HU - Hungary", "HU_temperature"}, {"IE - Ireland", "IE_temperature"},
        {"IT - Italy", "IT_temperature"}, {"LT - Lithuania", "LT_temperature"}, {"LU - Luxembourg", "LU_temperature"},
        {"LV - Latvia", "LV_temperature"}, {"NL - Netherlands", "NL_temperature"}, {"NO - Norway", "NO_temperature"},
        {"PL - Poland", "PL_temperature"}, {"PT - Portugal", "PT_temperature"}, {"RO - Romania", "RO_temperature"},
        {"SE - Sweden", "SE_temperature"}, {"SI - Slovenia", "SI_temperature"}, {"SK - Slovakia", "SK_temperature"},
    };

    // find the country in the map and return the corresponding temperature column name
    auto it = countryToColumn.find(country);
    if (it != countryToColumn.end()) {
        return it->second;
    } else {
        // if the country is not found, print an error message and return an empty string
        std::cerr << "Country not found: " << country << std::endl;
        return "";
    }
}

// converts a timestamp string to a date string based on the specified period
std::string CSVReader::timestampToDate(const std::string& timestamp, Period period) {
    // create a tm structure to hold the parsed time
    std::tm tm = {};
    // create a stringstream to parse the timestamp
    std::istringstream ssTime(timestamp);
    // parse the timestamp into the tm structure
    ssTime >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");

    // create a stringstream to format the date
    std::ostringstream oss;
    // format the date based on the specified period
    switch (period) {
        case Period::Day:
            // format the date as YYYY-MM-DD
            oss << std::put_time(&tm, "%Y-%m-%d");
            break;
        case Period::Month:
            // format the date as YYYY-MM
            oss << std::put_time(&tm, "%Y-%m");
            break;
        case Period::Year:
            // format the date as YYYY
            oss << std::put_time(&tm, "%Y");
            break;
    }
    // return the formatted date as a string
    return oss.str();
}

// checks if the given time matches the specified period
bool CSVReader::matchPeriod(const std::tm& tm, Period period, int day, int month, int year) {
    // check if the tm structure matches the specified day, month, or year
    switch (period) {
        case Period::Day:
            return (tm.tm_mday == day);
        case Period::Month:
            return (tm.tm_mon + 1 == month);
        case Period::Year:
            return (tm.tm_year + 1900 == year);
    }
    // return false if the period does not match
    return false;
}

// reads the weather data from the CSV file for the specified country and period
std::vector<WeatherData> CSVReader::readData(const std::string& country, Period period, int day, int month, int year) {
    // open the CSV file for reading
    std::ifstream file(filename);
    // create a vector to hold the weather data
    std::vector<WeatherData> data;
    std::string line, colname;
    std::vector<std::string> headers;

    // check if the file was successfully opened
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }

    // read the header line of the CSV file
    if (file.good()) {
        std::getline(file, line);
        std::stringstream ss(line);
        // split the header line into column names
        while (std::getline(ss, colname, ',')) {
            headers.push_back(colname);
        }
    }

    // get the temperature column name for the selected country
    std::string tempColumn = getTemperatureColumn(country);

    // read the remaining lines of the CSV file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::unordered_map<std::string, std::string> row;
        std::string val;

        // split the line into column values and store them in a map
        for (size_t i = 0; i < headers.size(); ++i) {
            std::getline(ss, val, ',');
            row[headers[i]] = val;
        }

        // get the timestamp from the row
        std::string timestamp = row["utc_timestamp"];
        if (timestamp.empty()) {
            continue;
        }

        // parse the timestamp into a tm structure
        std::tm tm = {};
        std::istringstream ssTime(timestamp);
        if (!(ssTime >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ"))) {
            continue;
        }

        // check if the tm structure matches the specified period
        bool matched = matchPeriod(tm, period, day, month, year);

        // if the period matches and the temperature column is found in the row
        if (matched) {
            if (row.find(tempColumn) != row.end()) {
                WeatherData weatherData;
                // store the timestamp and temperature in the WeatherData structure
                weatherData.date = timestamp;
                weatherData.temperature = std::stod(row[tempColumn]);
                // add the WeatherData structure to the data vector
                data.push_back(weatherData);
            }
        }
    }

    // close the CSV file
    file.close();
    // return the vector of weather data
    return data;
}
