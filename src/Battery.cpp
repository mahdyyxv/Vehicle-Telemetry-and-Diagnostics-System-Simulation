#include "Battery.hpp"
#include "Logger.hpp"
#include "Rpi_Connection.hpp"
#include <iostream>
#include <string>

std::string sensors::Battery::getValue() {

  if (!isUpdated_) {
    update();
    isUpdated_ = false;
  }

  return std::to_string(batteryVal_) + " % " + std::to_string(batteryTemp_) +
         " °C";
}

void sensors::Battery::update() {
  std::string BattTemp = Rpi::getInstance().getSensorsData("Bat Temp");
  std::string BattPerc = Rpi::getInstance().getSensorsData("Bat Perc");
  std::string logMsg;
  if (BattTemp == "NULL" || BattPerc == "NULL") {
    batteryTemp_ = 10 + (rand() % 491);
    batteryVal_ = 0 + (rand() % 101);
  } else {
    batteryTemp_ = std::stoi(BattTemp);
    batteryVal_ = std::stoi(BattPerc);
  }

  try {
    // Get the singleton logger instance and log the message
    Logger::getInstance().log("Battery Data : " + std::to_string(batteryVal_) +
                              " % " + std::to_string(batteryTemp_) + " °C");
  } catch (const std::exception &e) {
    std::cerr << "Error logging temperature: " << e.what() << std::endl;
  }
  isUpdated_ = true;
}
