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

## Usage
1. **Compile the Program**:
   ```bash
   g++ -o weather_analysis main.cpp candlestick.cpp candlestickDataProcessor.cpp candlestickPlotter.cpp CSVReader.cpp menu.cpp predictionMenu.cpp temperaturePrediction.cpp -std=c++11
