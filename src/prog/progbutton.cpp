/**
 * @file button.cpp
 * @brief Defines the button program
 * @author Aldem Pido
 */
#include "progbutton.h"

namespace Program {
ProgButton::ProgButton(Driver::Pca9685 &driver)
    : BaseProgram(driver, Configuration::Button::LIGHT, "Button"), _counter(0),
      _in(Configuration::Button::BUT_IN),
      _red(driver, Configuration::Button::IND_RED),
      _yellow(driver, Configuration::Button::IND_YELLOW),
      _green(driver, Configuration::Button::IND_GREEN) {};

void ProgButton::begin() {
  ProgButton::reset();
  _state = 1;
}

void ProgButton::update() {
  _in.loop(); // update the button
  switch (_state) {
  case 0: // reset
  case 2: // running, beacon activated
  case 3: // paused
  default:
    break;
  case 1: // running, beacon not activated
    if (_in.isPressed()) {
      _counter++;
      ProgButton::updateInd();
      switch (_counter) {
        _state = 2;                     // indicate beacon activated
        BaseProgram::updateBeaconLed(); // update the led
        break;
      }
    }
    break;
  }
}

void ProgButton::reset() {
  BaseProgram::reset(); // handles beacon led, state, etc...
  ProgButton::updateInd();
  _counter = 0;
  _red.set(0);
  _yellow.set(0);
  _green.set(0);
  _in.setDebounceTime(50);
}

void ProgButton::updateInd() {
  switch (_counter) {
  case 1:
    _red.set(255);
    break;
  case 2:
    _yellow.set(255);
    break;
  case 3:
    _green.set(255);
    break;
  }
}

} // namespace Program
