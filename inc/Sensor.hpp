#pragma once

template <typename T> class Sensor {
  virtual T getValue() = 0;
  virtual void update() = 0;
};
