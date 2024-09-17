#pragma once
#include "Battery.hpp" // Include the sensor headers here
#include "RadarSensor.hpp"
#include "SpeedSensor.hpp"
#include "TempSesnor.hpp"
#include "common.hpp"
#include <algorithm>
#include <map>
#include <string>

class Diagnostics {
public:
  Diagnostics() = default;
  Diagnostics(Diagnostics &&) = default;
  Diagnostics(const Diagnostics &) = default;
  Diagnostics &operator=(Diagnostics &&) = default;
  Diagnostics &operator=(const Diagnostics &) = default;
  ~Diagnostics() = default;
  void setLimits(const std::map<std::string, std::pair<int, int>> &limits);
  void logIssue();
  template <typename SensorType>
  common::ErrorCodes runDiagnostics(SensorType &sensorObj, const std::string &sensorName);

  private:
  std::map<std::string, std::pair<int, int>> limits;
  std::string issues = "Issues \n";
  common::ErrorCodes sensorCheck(const std::string &sensor, int val);
};

template <typename SensorType>
common::ErrorCodes Diagnostics::runDiagnostics(SensorType &sensorObj,
                                 const std::string &sensorName) {
    try {
        auto value = sensorObj.getValue();
        int intValue = 0;

        if (sensorName == "Battery Percentage") {
            intValue = std::stoi(value);
        } else if (sensorName == "Battery Temp") {
            auto it = std::find(value.begin(), value.end(), '%');
            if (it != value.end()) {
                value.erase(0, std::distance(value.begin(), it + 1));
                intValue = std::stoi(value);
            } else {
                issues += "Invalid format for Battery Temp.\n";
                 // Skip further processing if format is invalid
            }
        } else {
            intValue = std::stoi(value); // Assuming value is convertible to int
        }

        return sensorCheck(sensorName, intValue);
    } catch (const std::exception &e) {
        issues +=
            "Error processing sensor '" + sensorName + "': " + e.what() + "\n";
        return common::ErrorCodes::NOT_DEFINED;
    }
}
