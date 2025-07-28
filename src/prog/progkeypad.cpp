/**
 * @file keypad.cpp
 * @brief methods for keypad program
 * @author Aldem Pido
 */
#include "progkeypad.h"
namespace Program {
ProgKeypad::ProgKeypad(Driver::Pca9685 &driver)
    : _beacon(driver, Configuration::Keypad::LIGHT),
      _ind(driver, Configuration::Keypad::IND),
      _keypad(makeKeymap(Configuration::Keypad::keys),
              Configuration::Keypad::pin_rows,
              Configuration::Keypad::pin_column, Configuration::Keypad::ROW_NUM,
              Configuration::Keypad::COLUMN_NUM) {}
void ProgKeypad::begin() {
  _input_pass.reserve(32); // maximum input characters is 33, change if needed
  ProgKeypad::reset();
}

void ProgKeypad::update() {
    char key = _keypad.getKey();
    if(key) {
        if(key == '*') {
            _input_pass = "";
        } else if(key == '#') {
            if(Configuration::Keypad::password.equals(_input_pass)) {
                _beacon.set(Helper::Colors::)
            } else {

            }
        }
    }
}

void ProgKeypad::pause() {}

void ProgKeypad::reset() {
  _randomColor = random(5); // random num from 0-4
  _input_pass.remove(0);    // clears string
  _beacon.set(Helper::Colors::OFF);
  _ind.set(0);
}

void ProgKeypad::get
} // namespace Program
