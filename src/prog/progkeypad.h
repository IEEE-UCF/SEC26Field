/**
 * @file keypad.h
 * @brief defines the keypad program
 * @author Aldem Pido
 */
#ifndef PROGKEYPAD_H
#define PROGKEYPAD_H
#include "../driver/pca9685.h"
#include "../helper/rgbled.h"
#include "../config/settings.h"
#include <Keypad.h>

namespace Program {
  class ProgKeypad {
    public:
    ProgKeypad(Driver::Pca9685 &driver);
    void begin();
    void update();
    void pause();
    void reset();
    private:
    int _state; //holds state of program
    int _counter;
    Helper::RGBLed _beacon;
    Helper::Led _ind;
    Keypad _keypad;
    String _input_pass;
    int _randomColor

  };
};
#endif