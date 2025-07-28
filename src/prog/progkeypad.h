/**
 * @file keypad.h
 * @brief defines the keypad program
 * @author Aldem Pido
 */
#ifndef PROGKEYPAD_H
#define PROGKEYPAD_H
#include "../config/settings.h"
#include "../driver/pca9685.h"
#include "../helper/rgbled.h"
#include "baseprogram.h"
#include <Keypad.h>

namespace Program {
class ProgKeypad : public BaseProgram {
public:
  ProgKeypad(Driver::Pca9685 &driver);
  void begin() override;
  void update() override;
  void reset() override;

private:
  void updateInd();
  Helper::Led _ind;
  Keypad _keypad;
  String _input_pass;
};
}; // namespace Program
#endif