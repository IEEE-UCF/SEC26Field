#include "progsensor.h"
namespace Program {
ProgSensor::ProgSensor(Driver::Pca9685 &driver)
    : BaseProgram(driver, Configuration::Sensor::LIGHT, "Pressure"),
      _ind(driver, Configuration::Sensor::IND) {}

void ProgSensor::begin() {}

void ProgSensor::update() {
  bool result = ProgSensor::evaluateObject();
  switch (_state) {
  case RUNNING_OFF:
    if (!result) {
      _state = RUNNING_ON;
      BaseProgram::updateBeaconLed();
      ProgSensor::updateInd();
    }
    break;
  case CUSTOM1: // special case if sens is not high enough at the beginning,
    if (result) {
      _state = RUNNING_OFF;
      BaseProgram::updateBeaconLed();
      ProgSensor::updateInd();
    }
    break;
  case RESET:
  case PAUSE:
  case RUNNING_ON:
  default:
    break;
  }
}

void ProgSensor::reset() {
  BaseProgram::reset();    // handles beacon led, state, etc...
  ProgSensor::updateInd(); // updates indicator
  _reading = 0;
}

void ProgSensor::getReading() {
  _reading = analogRead(Configuration::Sensor::IND);
}

/**
 * Returns true if an object exists
 */
bool ProgSensor::evaluateObject() { return _reading >= 50; }

void ProgSensor::updateInd() {
  switch (_state) {
  case 0:
  case 1:
    _ind.set(0);
    break;
  case 2:
    _ind.set(255);
    break;
  case 3:
  default:
    break;
  }
}
} // namespace Program
