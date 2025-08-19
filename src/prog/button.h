/**
 * @file button.h
 * @brief Defines the button beacon program
 * @author Aldem Pido
 */
#ifndef BUTTONPROGRAM_H_
#define BUTTONPROGRAM_H_
#include "beaconprogram.h"
#include <ezButton.h>
namespace Program {
struct BeaconConfig {
  uint8_t kBut, cR, cY, cG, activation_c;
  Configuration::RgbSetup beacon;
  String identifier;
};
class Button : public BeaconProgram {
public:
  Button(Driver::Pca9685 &driver, BeaconConfig config);

  void Button::begin() override;
  void Button::update() override;
  void Button::pause() override;
  void Button::reset() override;

private:
  BeaconConfig _config;

  int _count;
  ezButton _redButton;
  Helper::Led _r;
  Helper::Led _y;
  Helper::Led _g;

  void Button::updateTrafficLight(int count);
};
}; // namespace Program

#endif
