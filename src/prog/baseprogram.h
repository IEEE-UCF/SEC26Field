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
    BaseProgram(Driver::Pca9685 &driver, Configuration::LedSetup &ledsetup);
    virtual void begin();
    virtual void update();
    virtual void pause();
    virtual void reset();
    virtual void displayInfo(Print &output) const;
    
    private:
    Driver::Pca9685 _driver;
    Helper::RGBLed _beacon;
    int _state;
    int _randomColor;
    int selectColor();
    Helper::Color getColor(int num);
  };
};//namespace Program

#endif