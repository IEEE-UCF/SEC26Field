/**
 * @file SEC26Beacons.ino
 * @brief main file
 * @author Aldem Pido
 */
#include <Arduino.h>
#include "src/prog/beacon_button.h";
#include "src/prog/beacon_crank.h";
#include "src/prog/beacon_keypad.h";
#include "src/prog/beacon_sensor.h";
#include "src/driver/pca9685.h";
#include "src/config/settings.h";

Driver::Pca9685 servodecoder1(0x00);
Driver::Pca9685 servodecoder2(0x01);

Program::Beacon_Button pr_button(servodecoder1);
Program::Beacon_Crank pr_crank(servodecoder1);
Program::Beacon_Keypad pr_key(servodecoder1);
Program::Beacon_Sensor pr_sens(servodecoder1);


void setup() {
  Serial.begin(9600);
  servodecoder1.begin();
  servodecoder2.begin();
  pr_button.begin();
  pr_crank.begin();
  pr_key.begin();
  pr_sens.begin();
  
}

void loop() {
  static long lastUpdate50Call;
  if(millis() - lastUpdate50Call > 50) {
    pr_button.update();
    pr_crank.update();
    pr_key.update();
    pr_sens.update();
  }
  lastUpdate50Call = millis(); 
}