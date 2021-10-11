
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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

// radio class
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  // Serial monitor
  Serial.begin(9600);

  // NRF24
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
}

void loop() {
  
  if (radio.available()) 
  {
    radio.read(&data, sizeof(Data_Pack));

    // Serial Print
    Serial.print("Data: ");
    Serial.println(data.RIGHT_J_Y);
    delay(100);
  }
  else
  {
    Serial.print("No connection ");
  }

}
