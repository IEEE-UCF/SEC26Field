int red = 9;
int green = 10;
int blue = 11;
int led_pin = 13;

// --- ESP32 LEDC PWM Setup ---
const int redChannel_sensor = 9;
const int greenChannel_sensor = 10;
const int blueChannel_sensor = 11;
const int freq_sensor = 5000;
const int resolution_sensor = 8;
// --- End ESP32 Setup ---

int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;
int randomColor;

int begin = 1;

// Define the ADC pin for the sensor. I think GPIO 35 is a good choice for ESP32.
const int sensorPin = 35; 

void setup() {
  Serial.begin(9600);
  // GPIO36 as a placeholder again
  randomSeed(analogRead(36)); 
  randomColor = random(1, 5);

  // --- ESP32 LEDC PWM Initialization ---
  ledcSetup(redChannel_sensor, freq_sensor, resolution_sensor);
  ledcSetup(greenChannel_sensor, freq_sensor, resolution_sensor);
  ledcSetup(blueChannel_sensor, freq_sensor, resolution_sensor);
  ledcAttachPin(red, redChannel_sensor);
  ledcAttachPin(green, greenChannel_sensor);
  ledcAttachPin(blue, blueChannel_sensor);
  // --- End ESP32 Initialization ---
  
  pinMode(led_pin, OUTPUT);
}

void loop() {
  int analogReading = analogRead(sensorPin); 
  if (begin == 1){
    begin = 0;
    while(analogRead(sensorPin) <= 50){
      redBrightness = 150;
      blueBrightness = 0;
      greenBrightness = 0;
      
      ledcWrite(redChannel_sensor, redBrightness);
      ledcWrite(greenChannel_sensor, greenBrightness);
      ledcWrite(blueChannel_sensor, blueBrightness);
      Serial.println("Error State");

      delay(250);
      ledcWrite(redChannel_sensor, 0);
      delay(250);
    }
    ledcWrite(redChannel_sensor, 0);
    ledcWrite(greenChannel_sensor, 100);
    delay(2000);
    ledcWrite(greenChannel_sensor, 0);
  }

  Serial.print("Force sensor reading = ");
  Serial.println(analogReading);

  if(analogReading <= 30){
    delay(500);
    if(analogRead(sensorPin) <= 30){
      Serial.println("Removed");

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
      ledcWrite(redChannel_sensor, redBrightness);
      ledcWrite(greenChannel_sensor, greenBrightness);
      ledcWrite(blueChannel_sensor, blueBrightness);
      // --- End ESP32 Write ---

      delay(3000); // Original bad behavior preserved
    }
  }

  delay(500); // Original bad behavior preserved
}
