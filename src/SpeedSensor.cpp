#include "SpeedSensor.hpp"
#include "Rpi_Connection.hpp"
#include "Logger.hpp"
#include <iostream>
#include <string>

std::string sensors::Speed::getValue() {
  if (!isUpdated_) {
    update();
    isUpdated_ = false;
  }
  return std::to_string(speedVal_);
}
void sensors::Speed::setValue(uint16_t val) {
  speedVal_ = val;
  Rpi::getInstance().getSensorsData("update Speed = " + std::to_string(speedVal_));
}
void sensors::Speed::update() {

  std::string speedData = Rpi::getInstance().getSensorsData("Speed");
  if (speedData == "NULL") {
    speedVal_ = 10 + (rand() % 291);
  } else {
    speedVal_ = std::stoi(speedData);
  }
  try {
    Logger::getInstance().log("Speed Data : " + std::to_string(speedVal_) +
                              "Km/h");
  } catch (const std::exception &e) {
    std::cerr << "Error logging temperature: " << e.what() << std::endl;
  }
  isUpdated_ = true;
}
