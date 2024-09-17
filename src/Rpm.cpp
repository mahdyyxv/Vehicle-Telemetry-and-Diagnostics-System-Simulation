#include "Rpm.hpp"
#include "Logger.hpp"
#include "Rpi_Connection.hpp"
#include <iostream>
#include <string>

std::string sensors::Rpm::getValue() {
  if (!isUpdated_) {
    update();
    isUpdated_ = false;
  }
  return std::to_string(RpmVal_);
}
void sensors::Rpm::update() {

  std::string distData = Rpi::getInstance().getSensorsData("Rpm");
  if (distData == "NULL") {
    RpmVal_ = (rand() % 7);
  } else {
    RpmVal_ = std::stoi(distData);
  }
  try {
    // Get the singleton logger instance and log the message
    Logger::getInstance().log("Rpm Data : " + std::to_string(RpmVal_) +
                              "m");
  } catch (const std::exception &e) {
    std::cerr << "Error logging temperature: " << e.what() << std::endl;
  }
  isUpdated_ = true;
}
