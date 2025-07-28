#include "beacon_sensor.h"
namespace Program {
Beacon_Sensor::Beacon_Sensor(Driver::Pca9685 &driver)
    : Program_Template(driver, Configuration::Sensor::LIGHT, "Pressure"),
      _ind(driver, Configuration::Sensor::IND) {}

void Beacon_Sensor::begin() {}

void Beacon_Sensor::update() {
  bool result = Beacon_Sensor::evaluateObject();
  switch (_state) {
  case RUNNING_OFF:
    if (!result) {
      _state = RUNNING_ON;
      Program_Template::updateBeacon();
      Beacon_Sensor::updateIndicator();
    }
    break;
  case CUSTOM1: // special case if sens is not high enough at the beginning,
    if (result) {
      _state = RUNNING_OFF;
      Program_Template::updateBeacon();
      Beacon_Sensor::updateIndicator();
    }
    break;
  case RESET:
  case PAUSE:
  case RUNNING_ON:
  default:
    break;
  }
}

void Beacon_Sensor::reset() {
  Program_Template::reset();    // handles beacon led, state, etc...
  Beacon_Sensor::updateIndicator(); // updates indicator
  _reading = 0;
}

void Beacon_Sensor::getReading() {
  _reading = analogRead(Configuration::Sensor::IND);
}

/**
 * Returns true if an object exists
 */
bool Beacon_Sensor::evaluateObject() { return _reading >= 50; }

void Beacon_Sensor::updateIndicator() {
  switch (_state) {
  case RESET:
  case RUNNING_OFF:
    _ind.set(0);
    break;
  case RUNNING_ON:
    _ind.set(255);
    break;
  case 3:
  default:
    break;
  }
}
} // namespace Program
