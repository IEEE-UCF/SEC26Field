/**
 * @file button.h
 * @brief Program for button beacon
 * @author Aldem Pido
 */

 /**
  * Program state definitions
  * 0: reset
  * 1: running, beacon not activated
  * 2: running, beacon activated
  * 3: paused
  */
#ifndef PROGBUTTON_H
#define PROGBUTTON_H

#include <ezButton.h>  // The library to use for SW pin

#include "../config/settings.h"
#include "../helper/rgbled.h"

namespace Program {
  class ProgButton {
    public:
    ProgButton(Driver::Pca9685 &driver);
    void begin();
    void update();
    void pause();
    void reset();
    private:
    int _state; //holds state of program
    int _counter;
    ezButton _in;
    Helper::RGBLed _beacon;
    Helper::Led _red;
    Helper::Led _yellow;
    Helper::Led _green;
  };
}; //namespace Program
#endif