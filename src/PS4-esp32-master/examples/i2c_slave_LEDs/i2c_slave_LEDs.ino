
// Include Arduino Wire library for I2C
#include <Wire.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Define LED Pin
const int ledPin = 15;  // 16 corresponds to GPIO16
const int LEDX_pin = 2;  // 16 corresponds to GPIO16
byte Data[2];

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;


// Variable for blink rate
int dutyCycle = 0;
int LEDX = 0;


void setup() {

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
  pinMode(LEDX_pin, OUTPUT);

  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);

  // Function to run when data received from master
  Wire.onReceive(receiveEvent);

  // Setup Serial Monitor
  Serial.begin(115200);
  Serial.println("I2C Slave Demonstration");
}



void receiveEvent(int len) {
  for (int i = 0; i < len; i++)
  {
    Data[i] = Wire.read();
  }
}


void loop() {
  
  delay(15);
  dutyCycle = Data[0];
  LEDX = Data[1];
  ledcWrite(ledChannel, dutyCycle);
  digitalWrite(LEDX_pin, LEDX);
}
