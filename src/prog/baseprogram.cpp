/**
 * @file baseprogram.h
 * @brief methods for each program
 * @author Aldem Pido
 */
#include "baseprogram.h"
namespace Program {
BaseProgram::BaseProgram(Driver::Pca9685 &driver,
                         Configuration::LedSetup &ledsetup)
    : _driver(driver), _beacon(driver, ledsetup), _state(0) {
  _randomColor = selectColor();
}

void BaseProgram::begin() {
  BaseProgram::reset();
  _state = 1;
}

void BaseProgram::update() { return; }

void BaseProgram::pause() { _state = 3; }

void BaseProgram::reset() {
  _state = 0;
  _randomColor = selectColor();
  _beacon.set(Helper::Colors::OFF);
}

void BaseProgram::displayInfo(Print &output) const {
  output.print("State: ");
  output.println(_state);
}

int BaseProgram::selectColor() { return random(4); }
Helper::Color BaseProgram::getColor(int num) {
  switch(num) {
    case 0:
    return Helper::Colors::RED;
    case 1:
    return Helper::Colors::BLUE;
    case 2:
    return Helper::Colors::GREEN;
    case 3:
    return Helper::Colors::PURPLE;
  }
}

} // namespace Program