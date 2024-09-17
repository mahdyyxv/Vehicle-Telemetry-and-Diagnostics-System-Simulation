#pragma once
#include "Sensor.hpp"
#include <cstdint>
#include <string>
namespace sensors {
class Radar : public Sensor<std::string> {
private:
  uint16_t distance_;
  bool isUpdated_;

public:
  Radar() = default;
  Radar(Radar &&) = default;
  Radar(const Radar &) = default;
  Radar &operator=(Radar &&) = default;
  Radar &operator=(const Radar &) = default;
  ~Radar() = default;
  std::string getValue() override;
  void update() override;
};
} // namespace sensors