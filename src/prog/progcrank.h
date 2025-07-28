/**
 * @file progcrank.h
 * @brief Header for crank program
 * @author Aldem Pido
 */
#ifndef PROGCRANK_H
#define PROGCRANK_H
#include "../config/settings.h"
#include "../driver/pca9685.h"
#include "../helper/rgbled.h"
#include "baseprogram.h"
#include <Arduino.h>


namespace Program {
class ProgCrank : public BaseProgram {
public:
  ProgCrank(Driver::Pca9685 &driver);
  void begin() override;
  void update() override;
  void reset() override;

private:
};
}; // namespace Program
#endif