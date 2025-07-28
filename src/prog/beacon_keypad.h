/**
 * @file keypad.h
 * @brief defines the keypad program
 * @author Aldem Pido
 */
#ifndef BEACON_KEYPAD_H
#define BEACON_KEYPAD_H
#include "../config/settings.h"
#include "../driver/pca9685.h"
#include "../helper/rgbled.h"
#include "program_template.h"
#include <Keypad.h>

namespace Program {
class Beacon_Keypadpad : public Program_Template {
public:
  Beacon_Keypadpad(Driver::Pca9685 &driver);
  void begin() override;
  void update() override;
  void reset() override;

private:
  void updateIndicator();
  Helper::Led _ind;
  Keypad _keypad;
  String _input_pass;
};
}; // namespace Program
#endif