
#pragma once

#include "RadarSensor.hpp"
#include "SpeedSensor.hpp"
#include "TempSesnor.hpp"
#include <cstdint>

namespace ecu {
constexpr uint16_t TEMP_MAX = 200;
constexpr uint16_t DIST_MIN = 50;

class Acc {
public:
    Acc() = default;
    Acc(Acc &&) = default;
    Acc(const Acc &) = default;
    Acc &operator=(Acc &&) = default;
    Acc &operator=(const Acc &) = default;
    ~Acc() = default;
    void tackAction(sensors::Temp &temp, sensors::Radar &radar,
                    sensors::Speed &speed);
};
} // namespace ecu
