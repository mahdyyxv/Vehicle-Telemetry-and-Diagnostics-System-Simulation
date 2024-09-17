#include "TempSesnor.hpp"
#include "Logger.hpp"
#include "Rpi_Connection.hpp"
#include <iostream>

std::string sensors::Temp::getValue() {
  if (!isUpdated_) {
    update();
    isUpdated_ = false;
  }

  return std::to_string(tempVal_);
}

void sensors::Temp::update() {
  std::string tempData = Rpi::getInstance().getSensorsData("Temp");
  if (tempData == "NULL") {
    tempVal_ = -40 + (rand() % 166);
  } else {
    tempVal_ = std::stoi(tempData);
  }
  try {
    Logger::getInstance().log("Temprature Data : " + std::to_string(tempVal_) +
                              "°C");
  } catch (const std::exception &e) {
    std::cerr << "Error logging temperature: " << e.what() << std::endl;
  }
  isUpdated_ = true;
}
