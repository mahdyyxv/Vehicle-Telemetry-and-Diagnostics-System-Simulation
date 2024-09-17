#include "Ecu.hpp"
#include <iostream>
#include <string>
#include <thread>

void ecu::Acc::tackAction(sensors::Temp &temp, sensors::Radar &radar, sensors::Speed &speed) {
 
  if (std::stoi(temp.getValue()) > TEMP_MAX) {
    speed.setValue(0); // make Car Stop
  }
  if (std::stoi(radar.getValue()) < DIST_MIN && std::stoi(speed.getValue()) != 0) {
    std::cout << "there is a problem" << std::endl;
    uint16_t speedVal = std::stoi(speed.getValue());
    speed.setValue((--speedVal));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    speed.getValue();
  }
}
