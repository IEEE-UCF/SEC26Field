/**
 * @file pca9685.cpp
 * @brief Implements PCA9685 routines
 * @author Aldem Pido
 */
#include "pca9685.h"

namespace Driver {

Pca9685::Pca9685(uint8_t addr) : _pwm(addr), _addr(addr) {}

void Pca9685::begin() {
  Wire.begin();
  _pwm.begin();
  _pwm.setPWMFreq(1000);
}

void Pca9685::setPwm(uint8_t channel, uint8_t value) {
  if (channel < 16) {
    uint16_t pwmValue = map(value, 0, 255, 0, 4095);
    _pwm.setPWM(channel, 0, pwmValue);
  }
}

void Pca9685::setPWMFreq(float freq) { _pwm.setPWMFreq(freq); }

} // namespace Driver