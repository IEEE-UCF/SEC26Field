/**
 * @file beacon_crank.cpp
 * @brief methods for crank
 * @author Aldem Pido
 */
#include "beacon_crank.h"
namespace Program {
Beacon_Crank::Beacon_Crank(Driver::Pca9685 &driver)
    : Program_Template(driver, Configuration::Crank::LIGHT, "Crank") {}

void Beacon_Crank::begin() {
  pinMode(Configuration::Crank::CLK_PIN, INPUT_PULLUP);
  pinMode(Configuration::Crank::DT_PIN, INPUT_PULLUP);
  /*attachInterrupt(digitalPinToInterrupt(Configuration::Crank::CLK_PIN),
                  Beacon_Crank::readEncoder, CHANGE);*/
  Beacon_Crank::reset();
  _state = RUNNING_OFF;
}

void Beacon_Crank::update() {
  switch (_state) {
  case RESET:
  case PAUSE:
  default:
    break;
  case RUNNING_OFF:
  case RUNNING_ON:
    readEncoder();
    bool newState;
    if (abs(_counter) == 18) {
      newState = RUNNING_ON;
    } else {
      newState = RUNNING_OFF;
    }
    if (newState != _state) {
      _state = newState;
      Beacon_Crank::updateIndicator();
      Program_Template::updateBeacon();
    }
  }
}

void Beacon_Crank::reset() {
  Program_Template::reset(); // handles beacon led, state, etc...
  _direction = DIRECTION_CW; // set direction to 0
  _counter = 0;              // reset counter
}

void Beacon_Crank::readEncoder() {
  int CLK_state = digitalRead(Configuration::Crank::CLK_PIN);
  if (CLK_state != _prev_CLK_state && CLK_state == HIGH) {
    if (digitalRead(Configuration::Crank::DT_PIN)) {
      _counter--;
      _direction = DIRECTION_CCW;
    } else {
      _counter++;
      _direction = DIRECTION_CW;
    }
  }
  _prev_CLK_state = CLK_state;
}

void Beacon_Crank::updateIndicator() {
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