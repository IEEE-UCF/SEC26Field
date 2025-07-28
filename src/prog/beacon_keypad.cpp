/**
 * @file progkeypad.cpp
 * @brief methods for keypad program
 * @author Aldem Pido
 */
#include "beacon_keypad.h"
namespace Program {
Beacon_Keypadpad::Beacon_Keypadpad(Driver::Pca9685 &driver)
    : Program_Template(driver, Configuration::Keypad::LIGHT, "Keypad"),
      _ind(driver, Configuration::Keypad::IND),
      _keypad(makeKeymap(Configuration::Keypad::keys),
              Configuration::Keypad::pin_rows,
              Configuration::Keypad::pin_column, Configuration::Keypad::ROW_NUM,
              Configuration::Keypad::COLUMN_NUM) {}

void Beacon_Keypadpad::begin() {
  _input_pass.reserve(32); // maximum input characters is 33, change if needed
  Beacon_Keypadpad::reset();
  _state = 1;
}

void Beacon_Keypadpad::update() {
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
      Beacon_Keypadpad::updateIndicator();
      Program_Template::updateBeacon();
    }
  }
}

void Beacon_Keypadpad::reset() {
  Program_Template::reset();    // handles beacon led, state, etc...
  Beacon_Keypadpad::updateIndicator(); // set indicator led to 0
  _input_pass.remove(0);   // clears string
}

void Beacon_Keypadpad::updateIndicator() {
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
