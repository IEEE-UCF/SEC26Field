/**
 * @file rgbled.cpp
 * @brief Implements rgb led methods
 * @author Aldem Pido
 */
#include "rgbled.h" // Include the corresponding header file
namespace Helper {

RGBLed::RGBLed(Driver::Pca9685 &driver, uint8_t cR, uint8_t cG, uint8_t cB)
    : _rLed(driver, cR), _gLed(driver, cG), _bLed(driver, cB) {
  // The PCA9685 driver's begin() method should be called once globally.
}

RGBLed::RGBLed(Driver::Pca9685 &driver, LedSetup setup)
    : _rLed(driver, setup.r), _gLed(driver, setup.g), _bLed(driver, setup.b) {
  // The PCA9685 driver's begin() method should be called once globally.
}

void RGBLed::set(Color color) { setRaw(color.r, color.g, color.b); }

// IMPORTANT: This implementation assumes common cathode RGB LEDs.
void RGBLed::setRaw(uint8_t strr, uint8_t strg, uint8_t strb) {
  _rLed.set(strr); // Set Red channel brightness
  _gLed.set(strg); // Set Green channel brightness
  _bLed.set(strb); // Set Blue channel brightness
}

} // namespace Helper