/**
 * @file progcrank.h
 * @brief Header for crank program
 * @author Aldem Pido
 */
#ifndef BEACON_CRANK_H
#define BEACON_CRANK_H
#include "../config/settings.h"
#include "../driver/pca9685.h"
#include "../helper/rgbled.h"
#include "program_template.h"
#include <Arduino.h>


namespace Program {
class Beacon_Crank : public Program_Template {
public:
  Beacon_Crank(Driver::Pca9685 &driver);
  void begin() override;
  void update() override;
  void reset() override;

private:
};
}; // namespace Program
#endif