#pragma once

#include "Sensor.hpp"
#include <cstdint>
#include <string>

namespace sensors {
class Battery : public Sensor<std::string> {
private:
  uint16_t batteryVal_;
  uint16_t batteryTemp_;
  bool isUpdated_ = false;

public:
  Battery() = default;
  Battery(Battery &&) = default;
  Battery(const Battery &) = default;
  Battery &operator=(Battery &&) = default;
  Battery &operator=(const Battery &) = default;
  ~Battery() = default;

  std::string getValue() override;
  void update() override;
};
} // namespace sensors
