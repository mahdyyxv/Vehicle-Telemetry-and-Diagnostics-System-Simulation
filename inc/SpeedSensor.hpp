#pragma once

#include "Sensor.hpp"
#include <cstdint>
#include <string>
namespace sensors {
class Speed : public Sensor<std::string> {
private:
  uint16_t speedVal_;
  bool isUpdated_;

public:
  Speed() = default;
  Speed(Speed &&) = default;
  Speed(const Speed &) = default;
  Speed &operator=(Speed &&) = default;
  Speed &operator=(const Speed &) = default;
  ~Speed() = default;
  std::string getValue() override;
  void setValue(uint16_t val);
  void update() override;
};
} // namespace sensors