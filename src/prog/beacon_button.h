/**
 * @file button.h
 * @brief Program for button beacon
 * @author Aldem Pido
 */
#ifndef BEACON_BUTTON_H
#define BEACON_BUTTON_H

#include <ezButton.h> // The library to use for SW pin

#include "../config/settings.h"
#include "../helper/rgbled.h"
#include "program_template.h"

namespace Program {
class Beacon_Button : public Program_Template {

public:
  Beacon_Button(Driver::Pca9685 &driver);
  void begin() override;
  void update() override;
  // void pause() override;
  void reset() override;

private:
  void updateIndicator();
  // int _state; inherited
  int _counter;
  ezButton _in;
  // Helper::RGBLed _beacon inherited
  Helper::Led _red;
  Helper::Led _yellow;
  Helper::Led _green;
};
}; // namespace Program
#endif