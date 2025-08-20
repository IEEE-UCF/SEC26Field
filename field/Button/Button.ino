#include <Arduino.h>
#include <ezButton.h>  // The library to use for SW pin, duh

#define SW_PIN 4

// these inline comments will be pretty different from my usual style
// since i want new people to understand this code 

// --- ESP32 LEDC PWM Setup ---
// On ESP32, analogWrite is different, we use the LEDC peripheral for PWM.
// Now we set up channels for each color of the RGB LED.
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int freq = 5000;
const int resolution = 8;
// --- End ESP32 Setup ---

int randomColor;
int counter = 0;

int red = 9;
int green = 10;
int blue = 11;

int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;
int redLED = 5;
int yellowLED = 6;
int greenLED = 7;
int led_pin = 13;

ezButton button(SW_PIN);

void setup() {
  Serial.begin(9600);

  // Use a valid ADC pin for ESP32, like GPIO 36 (its often marked A0 on dev boards!)
  randomSeed(analogRead(36)); 
  randomColor = random(1, 5);

  // --- ESP32 LEDC PWM Initialization ---
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  ledcAttachPin(red, redChannel);
  ledcAttachPin(green, greenChannel);
  ledcAttachPin(blue, blueChannel);
  // --- End ESP32 Initialization ---

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(led_pin, OUTPUT);

  // No need to set pinMode for red, green, blue as ledcAttachPin does it already.
}

void loop() {
  button.loop();
  if (button.isPressed()) {
    Serial.println("The button is pressed");
    counter++;
    if (counter == 1) { // First button press
      digitalWrite(redLED, HIGH);
    } 
    else if (counter == 2) { // Second button press
      digitalWrite(yellowLED, HIGH);
    }  
    else if (counter == 3) { // Third button press
      digitalWrite(greenLED, HIGH);
      if (randomColor == 1) {
        redBrightness = 150;
        blueBrightness = 0;
        greenBrightness = 0;
      } else if (randomColor == 2) {
        redBrightness = 0;
        blueBrightness = 150;
        greenBrightness = 0;
      } else if (randomColor == 3) {
        redBrightness = 0;
        blueBrightness = 0;
        greenBrightness = 100;
      } else {
        redBrightness = 200;
        blueBrightness = 150;
        greenBrightness = 0;
      }

      // --- ESP32 LEDC PWM Write ---
      ledcWrite(redChannel, redBrightness);
      ledcWrite(greenChannel, greenBrightness);
      ledcWrite(blueChannel, blueBrightness);
      // --- End ESP32 Write ---

      digitalWrite(led_pin, HIGH);
      delay(3000); // Original bad behavior preserved
    }
    delay(500); // Original bad behavior preserved

  }
}
