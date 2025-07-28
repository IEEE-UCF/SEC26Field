/**
 * @file button.cpp
 * @brief Defines the button program
 * @author Aldem Pido
 */
#include "progbutton.h"

namespace Program {
ProgButton::ProgButton(Driver::Pca9685 &driver)
    : _state(0), _counter(0), _in(Configuration::Button::BUT_IN),
      _beacon(driver, Configuration::Button::LIGHT),
      _red(driver, Configuration::Button::IND_RED),
      _yellow(driver, Configuration::Button::IND_YELLOW),
      _green(driver, Configuration::Button::IND_GREEN) {};

void ProgButton::begin() {
  _state = 1; // begin program
  _in.setDebounceTime(50);
}

void ProgButton::update() {
  _in.loop();
  switch (_state) {
  case 0: // reset
    break;
  case 1: // running, beacon not activated
    if (_in.isPressed()) {
      _counter++;
      switch (_counter) {
      case 1:
        _red.set(255);
        break;
      case 2:
        _yellow.set(255);
        break;
      case 3:
        _green.set(255);
        _state = 2; // indicate beacon activated
        break;
      }
    }
    break;
  case 2: // running, beacon activated
    // nothing happens here
    break;
  case 3: // paused
    // nothing happens here
    break;
  }
}

void ProgButton::pause() { _state = 3; }

void ProgButton::reset() {
  _state = 1;
  _counter = 0;
  _beacon.set(Helper::Colors::OFF);
  _red.set(0);
  _yellow.set(0);
  _green.set(0);
}

} // namespace Program
