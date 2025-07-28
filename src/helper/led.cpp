/**
 * @file rgbled.cpp
 * @brief Defines rgb led methods
 * @author Aldem Pido
 */

#include "led.h"

namespace Helper {
Led::Led(Driver::Pca9685 &driver, uint8_t c) : _driver(driver), _c(c) {}

void Led::set(uint8_t str) { _driver.setPwm(_c, str); }
} // namespace Helper