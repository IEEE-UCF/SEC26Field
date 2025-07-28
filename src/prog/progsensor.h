/**
 * @file progsensor.h
 * @brief Header for sensor program
 * @author Aldem Pido
 */
#ifndef PROGSENSOR_H
#define PROGSENSOR_H
#include "../config/settings.h"
#include "../driver/pca9685.h"
#include "../helper/rgbled.h"
#include "baseprogram.h"
#include <Arduino.h>


namespace Program {
class ProgSensor : public BaseProgram {
public:
  ProgSensor(Driver::Pca9685 &driver);
  void begin() override;
  void update() override;
  void reset() override;

private:
  void getReading();
  bool evaluateObject();
  void updateIndicator();
  Helper::Led _ind;
  int _reading;
};
}; // namespace Program
#endif