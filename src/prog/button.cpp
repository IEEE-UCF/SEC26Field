/**
 * @file button.cpp
 * @brief Implements the button beacon program
 * @author Aldem Pido
 */
#include "button.h"
namespace Program {
Button::Button(Driver::Pca9685 &driver, BeaconConfig &config)
    : BeaconProgram(driver, config.activation_c, config.beacon, config.identifier), _config(config),
      _redButton(config.kBut), _r(driver, config.cR), _y(driver, config.cY),
      _g(driver, config.cG) {}

void Button::update() {
  BeaconProgram::update();
  _redButton.loop(); // update the button
  unsigned long count = _redButton.getCount(); // get count
  switch (_state) {
  case 1:
  case 2:
    if (count >= 3) {
      _state = 2;
    } else {
      _state = 1;
    }
    break;
  case 0:
  case 3:
  default:
    break;
  }
  if (_redButton.isPressed()) {
    BeaconProgram::updateLed();
    Button::updateTrafficLight(count);
  }
}

/**
 * Updates the button's traffic light.
 * @param count button count.
 */
void Button::updateTrafficLight(int count) {
  switch (count) {
  case 0:
    _r.set(0);
    _y.set(0);
    _g.set(0);
    break;
  case 1:
    _r.set(255);
    _y.set(0);
    _g.set(0);
    break;
  case 2:
    _r.set(0);
    _y.set(255);
    _g.set(0);
    break;
  case 3:
  default:
    _r.set(0);
    _y.set(0);
    _g.set(255);
    break;
  }
}

void Button::reset() {
  BeaconProgram::reset();
  _redButton.setCountMode(COUNT_RISING);
  _redButton.resetCount();
  updateTrafficLight(_redButton.getCount()); // should pass 0 always
}
} // namespace Program