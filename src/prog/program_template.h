/**
 * @file program_template.h
 * @brief defines shared functions for each program
 * @author Aldem Pido
 */
#ifndef PROGRAM_TEMPLATE_H
#define PROGRAM_TEMPLATE_H

#include "../helper/rgbled.h"
#include <Arduino.h>

namespace Program {
class Program_Template {
public:
  enum States {
    RESET,
    RUNNING_OFF,
    RUNNING_ON,
    PAUSE,
    CUSTOM1,
    CUSTOM2
  };
  Program_Template(Driver::Pca9685 &driver, Configuration::LedSetup ledsetup,
              String identifier);
  virtual void begin();
  virtual void update();
  virtual void pause();
  virtual void reset();
  virtual void displayInfo(Print &output) const;
  void updateBeacon();

protected:
  Driver::Pca9685 _driver;
  Helper::RGBLed _beacon;
  String _identifier; // program name
  /**
   * 0: reset
   * 1: running, not activated
   * 2: running, activated
   * 3: paused
   * 4: custom1
   * 5: custom2
   * */
  int _state;
  int _randomColor;
  static int selectColor();
  static Helper::Color getColor(int num);
};
}; // namespace Program

#endif