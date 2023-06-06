
// Include Arduino Wire library for I2C
#include <Wire.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Define LED Pin
const int ledPin = 15;  // 16 corresponds to GPIO16

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;


// Variable for blink rate
int dutyCycle;


void setup() {

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);

  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);

  // Function to run when data received from master
  Wire.onReceive(receiveEvent);

  // Setup Serial Monitor
  Serial.begin(115200);
  Serial.println("I2C Slave Demonstration");
}


void receiveEvent(int len) {
  // read one character from the I2C
  dutyCycle = Wire.read();
  // Print value of incoming data


}
void loop() {
  delay(15);
  ledcWrite(ledChannel, dutyCycle);
}
