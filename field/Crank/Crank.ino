#include <Arduino.h>
#include <ezButton.h>  // The library to use for SW pin

#define SW_PIN 4

int CLK_PIN = 2;
int DT_PIN = 3;

int DIRECTION_CW = 0;   // clockwise direction
int DIRECTION_CCW = 1;  // anticlockwise direction

int counter = 0;
int direction = DIRECTION_CW;
int CLK_state;
int prev_CLK_state;

int red = 9;
int green = 10;
int blue = 11;
int led_pin = 13;

// --- ESP32 LEDC PWM Setup ---
const int redChannel_crank = 3;
const int greenChannel_crank = 4;
const int blueChannel_crank = 5;
const int freq_crank = 5000;
const int resolution_crank = 8;
// --- End ESP32 Setup ---

int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;

int randomColor;

void setup() {
  Serial.begin(9600);
  // Use a valid ADC pin for ESP32. Im using GPIO 36 again, change if you want
  randomSeed(analogRead(36)); 
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  
  // --- ESP32 LEDC PWM Initialization ---
  ledcSetup(redChannel_crank, freq_crank, resolution_crank);
  ledcSetup(greenChannel_crank, freq_crank, resolution_crank);
  ledcSetup(blueChannel_crank, freq_crank, resolution_crank);
  ledcAttachPin(red, redChannel_crank);
  ledcAttachPin(green, greenChannel_crank);
  ledcAttachPin(blue, blueChannel_crank);
  // --- End ESP32 Initialization ---
  
  pinMode(led_pin, OUTPUT);
  randomColor = random(1, 5);
  Serial.println(randomColor);

  prev_CLK_state = digitalRead(CLK_PIN);
}

void loop() {
  CLK_state = digitalRead(CLK_PIN);
  if (CLK_state != prev_CLK_state && CLK_state == HIGH) {
    if (digitalRead(DT_PIN) == HIGH) {
      counter--;
      direction = DIRECTION_CCW;
    } else {
      counter++;
      direction = DIRECTION_CW;
    }

    Serial.print(" - counter: ");
    Serial.println(counter);
    if((counter == 18) || (counter == -18)){
      Serial.print("LED On");
      digitalWrite(led_pin, HIGH);
      if(randomColor == 1)
      {
        redBrightness = 150;
        blueBrightness = 0;
        greenBrightness = 0;
      }
      else if(randomColor == 2)
      {
        redBrightness = 0;
        blueBrightness = 150;
        greenBrightness = 0;
      }
      else if(randomColor == 3)
      {
        redBrightness = 0;
        blueBrightness = 0;
        greenBrightness = 100;
      }
      else
      {
        redBrightness = 200;
        blueBrightness = 150;
        greenBrightness = 0; 
      }

      // --- ESP32 LEDC PWM Write ---
      ledcWrite(redChannel_crank, redBrightness);
      ledcWrite(greenChannel_crank, greenBrightness);
      ledcWrite(blueChannel_crank, blueBrightness);
      // --- End ESP32 Write ---

      delay(3000); // Original bad behavior preserved
    }
  }

  prev_CLK_state = CLK_state;
}