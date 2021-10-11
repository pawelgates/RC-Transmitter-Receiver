#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define PIN_LEFT_J_X        22
#define PIN_LEFT_J_Y        21
#define PIN_LEFT_J_PB       12
#define PIN_RIGHT_J_X       20
#define PIN_RIGHT_J_Y       19
#define PIN_RIGHT_J_PB      13
#define PIN_LEFT_PB         2
#define PIN_RIGHT_PB        1
#define PIN_LEFT_SW_UP      9
#define PIN_LEFT_SW_DOWN    8
#define PIN_RIGHT_SW_UP     7
#define PIN_RIGHT_SW_DOWN   6

typedef struct
{
  byte LEFT_J_X;        // Left Joystick X Axis
  byte LEFT_J_Y;        // Left Joystick Y Axis
  byte LEFT_J_PB;       // Left Joystick Push button
  byte RIGHT_J_X;       // Right Joystick X Axis
  byte RIGHT_J_Y;       // Right Joystick Y Axis
  byte RIGHT_J_PB;      // Right Joystick Push button
  byte LEFT_PB;         // Left Push button
  byte RIGHT_PB;        // Right Push button
  byte LEFT_SW_UP;      // Left Switch UP position
  byte LEFT_SW_DOWN;    // Left Switch DOWN position
  byte RIGHT_SW_UP;     // Right Switch UP position
  byte RIGHT_SW_DOWN;   // Right Switch DOWN position
  
} Data_Pack;

Data_Pack data;

// RADIO Class
RF24 radio(10, 11); // CE, CSN
const byte address[6] = "00001";

// OLED Class
Adafruit_SSD1306 oled(128, 64, &Wire, 4);

void setup()
{
  // Serial monitor
  Serial.begin(9600);

  // OLED
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();

  // NRF24
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);

  // Buttons/Switches pull-up resistors
  pinMode(PIN_LEFT_J_PB, INPUT_PULLUP);
  pinMode(PIN_RIGHT_J_PB, INPUT_PULLUP);
  pinMode(PIN_LEFT_PB, INPUT_PULLUP);
  pinMode(PIN_RIGHT_PB, INPUT_PULLUP);
  pinMode(PIN_LEFT_SW_UP, INPUT_PULLUP);
  pinMode(PIN_LEFT_SW_DOWN, INPUT_PULLUP);
  pinMode(PIN_RIGHT_SW_UP, INPUT_PULLUP);
  pinMode(PIN_RIGHT_SW_DOWN, INPUT_PULLUP);
}

void loop()
{
  // DATA READ
  data.LEFT_J_X = map(analogRead(A3), 0, 1023, 0, 255);
  data.LEFT_J_Y = map(analogRead(A2), 0, 1023, 0, 255);
  data.LEFT_J_PB = digitalRead(PIN_LEFT_J_PB);
  data.RIGHT_J_X = map(analogRead(A1), 0, 1023, 0, 255);
  data.RIGHT_J_Y = map(analogRead(A0), 0, 1023, 0, 255);
  data.RIGHT_J_PB = digitalRead(PIN_RIGHT_J_PB);
  data.LEFT_PB = digitalRead(PIN_LEFT_PB);
  data.RIGHT_PB = digitalRead(PIN_RIGHT_PB);
  data.LEFT_SW_UP = digitalRead(PIN_LEFT_SW_UP);
  data.LEFT_SW_DOWN = digitalRead(PIN_LEFT_SW_DOWN);
  data.RIGHT_SW_UP = digitalRead(PIN_RIGHT_SW_UP);
  data.RIGHT_SW_DOWN = digitalRead(PIN_RIGHT_SW_DOWN);

  // DATA SEND
  radio.write(&data, sizeof(Data_Pack));

  
  // OLED - Testing
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.println("HELLO");
  
  oled.setTextSize(3);
  oled.setCursor(0,20);
  oled.println(data.RIGHT_J_Y);

  oled.display();
  oled.clearDisplay();

  // Serial Print - Testing
  //Serial.println(data.LEFT_J_X);
  //Serial.println(data.LEFT_J_Y);
  //Serial.println(data.LEFT_J_PB);
  //Serial.println(data.RIGHT_J_X);
  Serial.println(data.RIGHT_J_Y);
  //Serial.println(data.RIGHT_J_PB);
  //Serial.println(data.LEFT_PB);
  //Serial.println(data.RIGHT_PB);
  //Serial.println(data.LEFT_SW_UP);
  //Serial.println(data.LEFT_SW_DOWN);
  //Serial.println(data.RIGHT_SW_UP);
  //Serial.println(data.RIGHT_SW_DOWN);
   
}
 
