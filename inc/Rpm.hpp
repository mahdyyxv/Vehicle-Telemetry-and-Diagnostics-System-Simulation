#pragma once
#include "Sensor.hpp"
#include <cstdint>
#include <string>

namespace sensors {
class Rpm : public Sensor<std::string> {
private:
  uint8_t RpmVal_;
  bool isUpdated_;

public:
  Rpm() = default;
  Rpm(Rpm &&) = default;
  Rpm(const Rpm &) = default;
  Rpm &operator=(Rpm &&) = default;
  Rpm &operator=(const Rpm &) = default;
  ~Rpm() = default;
  std::string getValue() override;
  void setValue(uint16_t val);
  void update() override;
};
} // namespace sensors
