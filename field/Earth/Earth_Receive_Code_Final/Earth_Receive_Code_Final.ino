// ESP32 COMPATIBLE VERSION - No changes were strictly necessary since IRremote v4+ is ESP32-ready,
// but i made sure that library and pins are compatible.

#include <IRremote.hpp>
#include <LiquidCrystal.h>
#define DECODE_NEC

/* for lcd connections*/
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
/* end of lcd connections */

/* start of LCD display control information */
const int ROWS = 6;
String result[ROWS][3] = { { "Ant_1", "OFF", "??" },
                        { "Ant_2", "OFF", "??" },
                        { "Ant_3", "OFF", "??" },
                        { "Ant_4", "OFF", "??" },
                        { "Wrong Color", "---", "" },
                        { "Connected","OFF",""} };
int row;
int antSent = -1;
unsigned long previousTime = 0;
unsigned long currentTime;
const long timeLimit = 1500;
int antName = 0;
int antStatus = 1;
int antColor = 2;
int antNamePos = 0;
int antStatusPos = 7;
int antColorPos = 13;
int wrongPos = 13;
int wrongColor = ROWS-2;
int rcvdComm = ROWS-1;
const int MAX_WRONG = 8;
int wrong = 0;
/* end of LCD display control information */

int baudRate = 9600;

// IR receiver pin, GPIO 15 is a safe choice on most ESP32s
int IRpin = 15; 
char antenna_mask = 0xf0;
char color_mask = 0x0f;
char rec_cmd;
char antenna_rec;
char color_rec;

void PrintResult(int lcdRow, int arrayRow) {
  lcd.setCursor(antNamePos, lcdRow);
  lcd.print(result[arrayRow][antName]);
  if (arrayRow == ROWS-2)
  {
    lcd.setCursor(wrongPos, lcdRow);
    lcd.print(result[arrayRow][antStatus]);
  }
  else if (arrayRow == ROWS -1)
  {
    lcd.setCursor(wrongPos, lcdRow);
    lcd.print(result[arrayRow][antStatus]);
  }
  else
  {
  lcd.setCursor(antStatusPos, lcdRow);
  lcd.print(result[arrayRow][antStatus]);
  
  lcd.setCursor(antColorPos, lcdRow);
  lcd.print(result[arrayRow][antColor]);
  }
}

void setup() {
  lcd.begin(16, 2);
  row = 0;
  PrintResult(0, row);
  row++;
  PrintResult(1, row);

  Serial.begin(baudRate);
  // The modern IRremote library handles ESP32 initialization correctly.
  IrReceiver.begin(IRpin, ENABLE_LED_FEEDBACK);
}

void loop() {
  currentTime = millis();
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == NEC) {
      rec_cmd = IrReceiver.decodedIRData.command;
      antenna_rec = rec_cmd & antenna_mask;
      color_rec = rec_cmd & color_mask;

      if (antenna_rec == 0x00) {
        Serial.println("Antenna 1");
        antSent = 0;
      } else if (antenna_rec == 0x30) {
        Serial.println("Antenna 2");
        antSent = 1;
      } else if (antenna_rec == 0x50) {
        Serial.println("Antenna 3");
        antSent = 2;
      } else if (antenna_rec == 0x60) {
        Serial.println("Antenna 4");
        antSent = 3;
      } else {
        Serial.println("Invalid Antenna");
        result[rcvdComm][antStatus] = "ON";
        antSent = -1;
      }

      if (antSent != -1) {
        result[antSent][antStatus] = "ON";
        result[rcvdComm][antStatus] = "ON";
        if (color_rec == 0x09) {
          Serial.println("Color: Red");
          result[antSent][antColor] = "RED";
        } else if (color_rec == 0x0A) {
          Serial.println("Color: Green");
          result[antSent][antColor] = "GRE";
        } else if (color_rec == 0x0C) {
          Serial.println("Color: Blue");
          result[antSent][antColor] = "BLU";
        } else if (color_rec == 0x0F) {
          Serial.println("Color: Purple");
          result[antSent][antColor] = "PUR";
        } else {
          Serial.println("Invalid Color");
          if (wrong < MAX_WRONG) {
            wrong++;
            result[wrongColor][antStatus] = String(wrong);
          }
        }
      }
    }
    IrReceiver.resume();
  }

  if (currentTime - previousTime >= timeLimit) {
    previousTime = currentTime;
    lcd.clear();
    PrintResult(0, row);
    row++;
    row = row % ROWS;
    PrintResult(1, row);
  }
}
