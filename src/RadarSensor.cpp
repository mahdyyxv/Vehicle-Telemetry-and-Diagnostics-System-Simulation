
#include "RadarSensor.hpp"
#include "Logger.hpp"
#include "Rpi_Connection.hpp"
#include <iostream>
#include <string>

std::string sensors::Radar::getValue() {
  if (!isUpdated_) {
    update();
    isUpdated_ = false;
  }
  return std::to_string(distance_);
}
void sensors::Radar::update() {

  std::string distData = Rpi::getInstance().getSensorsData("Dist");
  if (distData == "NULL") {
    distance_ = 10 + (rand() % 991);
  } else {
    distance_ = std::stoi(distData);
  }
  try {
    // Get the singleton logger instance and log the message
    Logger::getInstance().log("Radar Data : " + std::to_string(distance_) +
                              "m");
  } catch (const std::exception &e) {
    std::cerr << "Error logging temperature: " << e.what() << std::endl;
  }
  isUpdated_ = true;
}
