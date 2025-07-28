/**
 * @file progkeypad.cpp
 * @brief methods for keypad program
 * @author Aldem Pido
 */
#include "progkeypad.h"
namespace Program {
ProgKeypad::ProgKeypad(Driver::Pca9685 &driver)
    : BaseProgram(driver, Configuration::Keypad::LIGHT, "Keypad"),
      _ind(driver, Configuration::Keypad::IND),
      _keypad(makeKeymap(Configuration::Keypad::keys),
              Configuration::Keypad::pin_rows,
              Configuration::Keypad::pin_column, Configuration::Keypad::ROW_NUM,
              Configuration::Keypad::COLUMN_NUM) {}

void ProgKeypad::begin() {
  _input_pass.reserve(32); // maximum input characters is 33, change if needed
  ProgKeypad::reset();
  _state = 1;
}

void ProgKeypad::update() {
  switch (_state) {
  case 0:
  case 2:
  case 3:
  default:
    break;
  case 1:
    char key = _keypad.getKey();
    if (key) {
      if (key == '*') {
        _input_pass.remove(0); // clears string
      } else if (key == '#') {
        if (Configuration::Keypad::password.equals(_input_pass)) {
          _state = 2;
        } else {
          _state = 1;
        }
      } else {
        _input_pass.concat(key);
      }
      ProgKeypad::updateIndicator();
      BaseProgram::updateBeacon();
    }
  }
}

void ProgKeypad::reset() {
  BaseProgram::reset();    // handles beacon led, state, etc...
  ProgKeypad::updateIndicator(); // set indicator led to 0
  _input_pass.remove(0);   // clears string
}

void ProgKeypad::updateIndicator() {
  switch (_state) {
  case RESET:
  case RUNNING_OFF:
    _ind.set(0);
    break;
  case RUNNING_ON:
    _ind.set(255);
    break;
  case PAUSE:
  default:
    break;
  }
}

} // namespace Program
