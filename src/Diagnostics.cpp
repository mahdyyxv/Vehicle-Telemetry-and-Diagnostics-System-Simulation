#include "Diagnostics.hpp"
#include "Logger.hpp"
#include <iostream>
#include <string>


void Diagnostics::setLimits(
    const std::map<std::string, std::pair<int, int>> &limits) {
  this->limits = limits;
}



common::ErrorCodes Diagnostics::sensorCheck(const std::string &sensor, int val) {
  auto it = limits.find(sensor);
  if (it != limits.end()) {
    const auto &[minLimit, maxLimit] = it->second;
    if (val > maxLimit || val < minLimit) {
      issues += "Issue detected in sensor '" + sensor + "': Value " +
                std::to_string(val) + " is out of range [" +
                std::to_string(minLimit) + ", " + std::to_string(maxLimit) +
                "]\n";
        return common::ErrorCodes::ERROR;
    }
  } else {
    issues += "No limits found for sensor '" + sensor + "'\n";
      return common::ErrorCodes::NOT_DEFINED;
  }
  return common::ErrorCodes::NORMAL;
}

void Diagnostics::logIssue() {
  try {
    // Get the singleton logger instance and log the message
    Logger::getInstance().log("__________________________________________________\n");

    Logger::getInstance().log(issues);
    
    Logger::getInstance().log("__________________________________________________\n");
    
    issues.clear();
  } catch (const std::exception &e) {
    std::cerr << "Error logging issues: " << e.what() << std::endl;
  }
}


// Explicit template instantiation for specific sensor types
template common::ErrorCodes Diagnostics::runDiagnostics<sensors::Battery>(sensors::Battery &sensorObj, const std::string &sensorName);
template common::ErrorCodes Diagnostics::runDiagnostics<sensors::Radar>(sensors::Radar &sensorObj, const std::string &sensorName);
template common::ErrorCodes Diagnostics::runDiagnostics<sensors::Speed>(sensors::Speed &sensorObj, const std::string &sensorName);
template common::ErrorCodes Diagnostics::runDiagnostics<sensors::Temp>(sensors::Temp &sensorObj, const std::string &sensorName);
