/**
 * @file button.cpp
 * @brief Defines the button program
 * @author Aldem Pido
 */
#include "beacon_button.h"

namespace Program {
Beacon_Button::Beacon_Button(Driver::Pca9685 &driver)
    : Program_Template(driver, Configuration::Button::LIGHT, "Button"), _counter(0),
      _in(Configuration::Button::BUT_IN),
      _red(driver, Configuration::Button::IND_RED),
      _yellow(driver, Configuration::Button::IND_YELLOW),
      _green(driver, Configuration::Button::IND_GREEN) {};

void Beacon_Button::begin() {
  Beacon_Button::reset();
  _state = RUNNING_OFF;
}

void Beacon_Button::update() {
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
      Beacon_Button::updateIndicator();
      if(_counter == 3) {
        _state = 2;                     // indicate beacon activated
        Program_Template::updateBeacon(); // update the led
      }
    }
    break;
  }
}

void Beacon_Button::reset() {
  Program_Template::reset(); // handles beacon led, state, etc...
  Beacon_Button::updateIndicator();
  _counter = 0;
  _red.set(0);
  _yellow.set(0);
  _green.set(0);
  _in.setDebounceTime(50);
}

void Beacon_Button::updateIndicator() {
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
