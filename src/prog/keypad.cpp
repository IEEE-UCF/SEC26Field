/**
 * @file keypad.cpp
 * @brief Implements the keypad beacon program.
 * @author Aldem Pido
 */
#include "keypad.h"
namespace Program {
KeypadProgram::KeypadProgram(Driver::Pca9685 &driver, KeypadConfig &config)
    : BeaconProgram(driver, config.activation_c, config.beacon,
                    config.identifier),
      _config(config), _keypad(makeKeymap(keys), config.pin_rows,
                               config.pin_columns, ROW_NUM, COLUMN_NUM),
      _input_password() {
  _input_password.reserve(32); // set maximum password input length
  reset();
}

void KeypadProgram::update() {
  BeaconProgram::update();
  switch (_state) {
  case 1:
    char key = _keypad.getKey();
    if (key) {
      if (key == '*') { // equivalent of "reset"
        _input_password.clear();
      } else if (key == '#') {                  // equivalent of "enter"
        if (password.equals(_input_password)) { // correct
          _state = 2;
          BeaconProgram::updateLed();
        } else { // wrong
          _input_password.clear();
        }
      }
    }
    break;
  case 2:
  case 0:
  case 3:
  default:
    break;
  }
}

void KeypadProgram::reset() {
  BeaconProgram::reset();
  _input_password.clear();
}
} // namespace Program