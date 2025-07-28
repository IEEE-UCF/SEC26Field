/**
 * @file baseprogram.h
 * @brief methods for each program
 * @author Aldem Pido
 */
#include "baseprogram.h"
namespace Program {
/**
 * Constructor.
 */
BaseProgram::BaseProgram(Driver::Pca9685 &driver,
                         Configuration::LedSetup ledsetup, String identifier)
    : _driver(driver), _beacon(driver, ledsetup), _identifier(identifier),
      _state(0) {
  _randomColor = selectColor();
}

/**
 * Begins the program. Calls the reset function, then sets the state to "1"
 * (running, not activated).
 */
void BaseProgram::begin() {
  BaseProgram::reset();
  _state = RUNNING_OFF;
}

/**
 * Updates the program. Must be overridden.
 */
void BaseProgram::update() { return; }

/**
 * Pauses the program. Sets the state to "3" (paused).
 */
void BaseProgram::pause() { _state = PAUSE; }

/**
 * Resets the program. Sets the state to "0" (reset).
 */
void BaseProgram::reset() {
  _state = RESET;
  _randomColor = selectColor();
  BaseProgram::updateBeacon(); // update the beacon
}

/**
 * Displays info of state.
 * @param output Serial pointer
 */
void BaseProgram::displayInfo(Print &output) const {
  output.print("Program: ");
  output.print(_identifier);
  output.print("State: ");
  output.print(_state);
  output.print("Color: ");
  output.println(_randomColor);
}

/**
 * Updates the beacon LED based on state. Should only be called when necessary
 * @param state use _state
 */
void BaseProgram::updateBeacon() {
  switch (_state) {
  case RUNNING_OFF: // running, not activated
    _beacon.set(Helper::Colors::OFF);
    break;
  case RUNNING_ON: // running, activated
    _beacon.set(BaseProgram::getColor(_state));
    break;
  case RESET: // reset
  case PAUSE: // paused, do nothing
  default:
    break;
  }
}

/**
 * Returns a random int from 0-4.
 * @return int
 */
int BaseProgram::selectColor() { return random(4); }

/**
 * Returns the color for a int from 0-4.
 * @return Helper::Color
 */
Helper::Color BaseProgram::getColor(int num = -1) {
  switch (num) {
  case 0:
    return Helper::Colors::RED;
  case 1:
    return Helper::Colors::BLUE;
  case 2:
    return Helper::Colors::GREEN;
  case 3:
    return Helper::Colors::PURPLE;
  default:
    return Helper::Colors::OFF;
  }
}

} // namespace Program