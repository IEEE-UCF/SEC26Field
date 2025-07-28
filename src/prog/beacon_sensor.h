/**
 * @file progsensor.h
 * @brief Header for sensor program
 * @author Aldem Pido
 */
#ifndef BEACON_SENSOR_H
#define BEACON_SENSOR_H
#include "../config/settings.h"
#include "../driver/pca9685.h"
#include "../helper/rgbled.h"
#include "program_template.h"
#include <Arduino.h>


namespace Program {
class Beacon_Sensor : public Program_Template {
public:
  Beacon_Sensor(Driver::Pca9685 &driver);
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