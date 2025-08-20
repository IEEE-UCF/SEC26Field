#include <Keypad.h>

int red = 9;
int green = 10;
int blue = 11;
int led_pin = 13;

// --- ESP32 LEDC PWM Setup ---
const int redChannel_keypad = 6;
const int greenChannel_keypad = 7;
const int blueChannel_keypad = 8;
const int freq_keypad = 5000;
const int resolution_keypad = 8;
// --- End ESP32 Setup ---

int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;
int randomColor;

const int ROW_NUM = 4;
const int COLUMN_NUM = 3;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

// Changed to common ESP32 GPIO pins, you can adjust these as needed
byte pin_rows[ROW_NUM] = {19, 18, 5, 17};
byte pin_column[COLUMN_NUM] = {16, 4, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
const String password = "73738";
String input_password;

void setup(){
  Serial.begin(9600);
  input_password.reserve(32);
  // Using GPIO 36 as a placeholder again!
  randomSeed(analogRead(36)); 
  randomColor = random(5);
  Serial.println(randomColor);

  // --- ESP32 LEDC PWM Initialization ---
  ledcSetup(redChannel_keypad, freq_keypad, resolution_keypad);
  ledcSetup(greenChannel_keypad, freq_keypad, resolution_keypad);
  ledcSetup(blueChannel_keypad, freq_keypad, resolution_keypad);
  ledcAttachPin(red, redChannel_keypad);
  ledcAttachPin(green, greenChannel_keypad);
  ledcAttachPin(blue, blueChannel_keypad);
  // --- End ESP32 Initialization ---
  
  pinMode(led_pin, OUTPUT);
}

void loop(){
  char key = keypad.getKey();

  if (key){
    Serial.println(key);
    if(key == '*') {
      input_password = "";
    } 
    else if(key == '#') {
      if(password == input_password) {
        Serial.println("password is correct");
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
        ledcWrite(redChannel_keypad, redBrightness);
        ledcWrite(greenChannel_keypad, greenBrightness);
        ledcWrite(blueChannel_keypad, blueBrightness);
        // --- End ESP32 Write ---

        digitalWrite(led_pin, HIGH);
        delay(3000); // Preserving that original bad behavior
        input_password = "";
        } 
        else {
          Serial.println("password is incorrect, try again");
          input_password = "";
        }
    } 
    else {
      input_password += key;
    }
  }
}