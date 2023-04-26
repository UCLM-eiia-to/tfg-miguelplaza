
// Include Arduino Wire library for I2C
#include <Wire.h>
#include <PS4Controller.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Integer to hold potentiometer value
int var1 = 0;
int var2 = 0;

void setup() {

  // Initialize I2C communications as Master
  Wire.begin();
  Serial.begin(115200);
  PS4.begin("28:66:e3:3b:75:eb");
  Serial.println("Ready.");


}

void loop() {
  if (PS4.isConnected())
  {
    delay(50);

    // Read pot value
    // Map to range of 1-255 for flash rate
    var1 = PS4.R2Value();
    var2 = PS4.Cross();

    // Write a charatre to the Slave
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(var1);
    Wire.write(var2);
    Wire.endTransmission();
    Serial.println(var1);
    Serial.println(var2);
  }


}
