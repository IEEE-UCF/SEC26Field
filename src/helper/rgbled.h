/**
 * @file rgbled.h
 * @brief Defines rgb led methods
 * @author Aldem Pido
 */
#ifndef RGBLED_h
#define RGBLED_h

#include "../driver/pca9685.h"
#include "led.h"
#include "../config/settings.h"
#include <Arduino.h>

namespace Helper {
using Configuration::LedSetup;
struct Color {
  const uint8_t r;
  const uint8_t g;
  const uint8_t b;
  constexpr Color(const uint8_t _r, const uint8_t _g, const uint8_t _b)
      : r(_r), g(_g), b(_b) {}
};

namespace Colors {
  constexpr Color RED(150, 0, 0);
  constexpr Color BLUE(0, 0, 150);
  constexpr Color GREEN(0, 100, 0);
  constexpr Color PURPLE(200, 0, 150);
  constexpr Color OFF(0, 0, 0);
};

class RGBLed {
public:
  RGBLed(Driver::Pca9685 &driver, uint8_t cR, uint8_t cG, uint8_t cB);
  RGBLed(Driver::Pca9685 &driver, LedSetup setup);
  void set(Color color);
  void setRaw(uint8_t strr, uint8_t strg, uint8_t strb);

private:
  Led _rLed;
  Led _gLed;
  Led _bLed;
};
}; // namespace Helper

#endif