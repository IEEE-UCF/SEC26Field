/**
 * @file lcd.h
 * @brief Defines the lcd wrapper class for LiquidCrystal.h
 * @author Aldem Pido
 */
#include <LiquidCrystal.h>
namespace Driver {
struct LCDConfig {
  uint8_t rs, en, d4, d5, d6, d7;
};
struct LCDAdvanced {
  
};
class LCD {
public:
LCD::LCD(LCDConfig &config);
private:
LCDConfig &_config;


};
};