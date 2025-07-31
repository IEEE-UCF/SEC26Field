/**
 * @file pca9685.h
 * @brief Defines PCA9685 routines
 * The PCA9685 can control up to 16 PWM output channels at a time. They are
 * being used for LEDs.
 * @author Aldem Pido
 */
#ifndef PCA9685_h
#define PCA9685_h

#include <Adafruit_PWMServoDriver.h> // PCA9685 library
#include <Arduino.h>
#include <Wire.h> // Required for I2C communication

namespace Driver {
class Pca9685 {
public:
  Pca9685(uint8_t addr = 0x40);

  void begin();
  void setPwm(uint8_t channel, uint8_t value);
  void setPWMFreq(float freq);
  uint8_t returnAddr() { return _addr; };

private:
  Adafruit_PWMServoDriver _pwm;
  uint8_t _addr;
};
}; // namespace Driver
#endif
