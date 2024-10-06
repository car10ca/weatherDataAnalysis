# Weather Analysis Toolkit

## Overview
This repository contains the implementation of a command-line weather analysis toolkit, developed as part of the **CM2005 Object Oriented Programming** midterm assignment for the BSc in Computer Science program. The toolkit is designed to visualize and predict weather data for various European countries using candlestick data representations and a text-based plotting system.

## Features
The toolkit offers the following features:

- **Compute Candlestick Data**:
  - Calculates the Open, High, Low, and Close values for temperature data, using different time frames (daily, monthly, or yearly).
  - Outputs candlestick data for easy visualization and analysis.
  
- **Text-based Candlestick Plotting**:
  - Creates text-based plots of the computed candlestick data, allowing users to visualize trends over time.

- **Data Filtering**:
  - Filters data based on country, date range, and temperature data range, providing flexibility in data selection.

- **Prediction of Future Temperatures**:
  - Uses historical temperature data to predict future temperatures and generates a textual graph to display the results.

## Files in the Repository

- **`candlestick.h` and `candlestick.cpp`**: Defines the `Candlestick` class, which stores information about each candlestick (Open, High, Low, Close temperatures).
- **`candlestickDataProcessor.h` and `candlestickDataProcessor.cpp`**: Implements functions to process weather data and generate candlestick objects for daily, monthly, or yearly time frames.
- **`candlestickPlotter.h` and `candlestickPlotter.cpp`**: Contains the functionality to create text-based plots of candlestick data.
- **`CSVReader.h` and `CSVReader.cpp`**: Parses CSV files and reads weather data for the specified country and period.
- **`menu.h` and `menu.cpp`**: Implements a text-based menu interface for user interaction, allowing selection of country, time frame, and data representation type.
- **`predictionMenu.h` and `predictionMenu.cpp`**: Contains the prediction menu for forecasting future temperatures based on historical data.
- **`temperaturePrediction.h` and `temperaturePrediction.cpp`**: Predicts future temperatures and generates a textual graph for visualization.
- **`main.cpp`**: Entry point of the program, which initializes the menu and drives the application logic.

## Installation

### Prerequisites
To compile and run this program, ensure that you have the following installed:

- A C++ compiler that supports C++11 (e.g., `g++` or `clang++`).
- Standard C++ libraries.
- Command-line interface access (Terminal on macOS/Linux, Command Prompt on Windows).

### Compiling the Program
Navigate to the root directory of this project and run the following command to compile the program:

```bash```
g++ -o weather_analysis main.cpp candlestick.cpp candlestickDataProcessor.cpp candlestickPlotter.cpp CSVReader.cpp menu.cpp predictionMenu.cpp temperaturePrediction.cpp -std=c++11


### Running the Program
Once compiled, you can run the program using the following command:

```bash```
./weather_analysis

## Navigating the Program
Upon running the program, you will see the following main menu:

====================
#### WEATHER ANALYSIS
====================
1. Analyse existing data
2. Predict future (2020) temperatures
3. Exit

You can navigate through the menu by entering the corresponding number (e.g., 1 to analyze existing data).

#### Analyzing Existing Data
- Select a country (e.g., Germany, France) from the list.
- Choose a time frame (day, month, or year).
- Choose how to view the data: Tabular data or Text-based plot.

#### Predicting Future Temperatures
- Choose a country to predict the temperature for the year 2020.
- View the output in a text-based graph format.

##### Example Output
The program outputs candlestick data in the following format:
- Date: 1980-01-01 | --------------------------|------------------ Open: -1.249  High: 20  Low: -3  Close: -1.200
- Date: 1981-01-01 | ---------------------------|----------------- Open: -1.200  High: 25  Low: -2  Close: -1.300

Additionally, a text-based graph of predicted temperatures is generated using * to represent temperature values on a day-by-day basis.


### Predicting Future Temperatures
The program uses historical averages to forecast daily temperatures for the selected country in the year 2020. It generates a daily prediction and visualizes the trend using a text-based graph.

### License
This project is licensed under the MIT License. See the LICENSE file for more details.

### Author
This project was developed as part of a university midterm assignment for the CM2005 Object Oriented Programming course in the BSc Computer Science program.

Developed by: Kerstin Kegel
GitHub: car10ca
