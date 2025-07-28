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
  _state = RUNNING_OFF;
}

void ProgButton::update() {
  _in.loop(); // update the button
  switch (_state) {
  case RESET: // reset
  case RUNNING_ON: // running, beacon activated
  case PAUSE: // paused
  default:
    break;
  case RUNNING_OFF: // running, beacon not activated
    if (_in.isPressed()) {
      _counter++;
      ProgButton::updateIndicator();
      if(_counter == 3) {
        _state = 2;                     // indicate beacon activated
        BaseProgram::updateBeacon(); // update the led
      }
    }
    break;
  }
}

void ProgButton::reset() {
  BaseProgram::reset(); // handles beacon led, state, etc...
  ProgButton::updateIndicator();
  _counter = 0;
  _red.set(0);
  _yellow.set(0);
  _green.set(0);
  _in.setDebounceTime(50);
}

void ProgButton::updateIndicator() {
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
