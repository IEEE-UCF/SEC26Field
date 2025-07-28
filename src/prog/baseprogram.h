/**
 * @file baseprogram.h
 * @brief defines shared functions for each program
 * @author Aldem Pido
 */
#ifndef BASEPROGRAM_H
#define BASEPROGRAM_H

#include "../helper/rgbled.h"
#include <Arduino.h>

namespace Program {
class BaseProgram {
public:
  enum States {
    RESET,
    RUNNING_OFF,
    RUNNING_ON,
    PAUSE,
    CUSTOM1,
    CUSTOM2
  };
  BaseProgram(Driver::Pca9685 &driver, Configuration::LedSetup ledsetup,
              String identifier);
  virtual void begin();
  virtual void update();
  virtual void pause();
  virtual void reset();
  virtual void displayInfo(Print &output) const;
  void updateBeaconLed();

protected:
  Driver::Pca9685 _driver;
  Helper::RGBLed _beacon;
  String _identifier; // program name
  /**
   * 0: reset
   * 1: running, not activated
   * 2: running, activated
   * 3: paused
   * */
  int _state;
  int _randomColor;
  static int selectColor();
  static Helper::Color getColor(int num);
};
}; // namespace Program

#endif