#pragma once

#include "Sensor.hpp"
#include <cstdint>
#include <string>
namespace sensors {
class Temp : public Sensor<std::string> {
private:
  int16_t tempVal_;
  bool isUpdated_;

public:
  Temp() = default;
  Temp(Temp &&) = default;
  Temp(const Temp &) = default;
  Temp &operator=(Temp &&) = default;
  Temp &operator=(const Temp &) = default;
  ~Temp() = default;
  std::string getValue() override;
  void update() override;
};
} // namespace sensors