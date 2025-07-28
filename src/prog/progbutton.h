/**
 * @file button.h
 * @brief Program for button beacon
 * @author Aldem Pido
 */

/**
 * Program state definitions
 * 0: reset
 * 1: running, beacon not activated
 * 2: running, beacon activated
 * 3: paused
 */
#ifndef PROGBUTTON_H
#define PROGBUTTON_H

#include <ezButton.h> // The library to use for SW pin

#include "../config/settings.h"
#include "../helper/rgbled.h"
#include "baseprogram.h"

namespace Program {
class ProgButton : public BaseProgram {

public:
  ProgButton(Driver::Pca9685 &driver);
  void begin() override;
  void update() override;
  // void pause() override;
  void reset() override;

private:
  void updateInd();
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