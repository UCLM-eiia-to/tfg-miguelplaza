#include <Wire.h>

#include <Gamepad.h>

// Define Slave I2C Address
#define SLAVE_ADDR 9


int RXStick = 0;
int RYStick = 0;
int LXStick = 0;
int LYStick = 0;

int leftxJoystickValue = 0;
int leftyJoystickValue = 0;
int rightxJoystickValue = 0;
int rightyJoystickValue = 0;

byte Data[18];

Gamepad gp;

void setup() {

  // Setup Serial Monitor
  Serial.begin(115200);
  Serial.println("USB keyboard");

  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);

  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
  Wire.setClock(100000);

}

void receiveEvent(int len) {
  for (int i = 0; i < len; i++)
  {
    Data[i] = Wire.read();
  }
}

void loop() {

  LXStick = Data[14];
  LYStick = Data[15];
  RXStick = Data[16];
  RYStick = Data[17];

  leftxJoystickValue = map(LXStick, 0, 255, -127, 127);
  leftyJoystickValue = map(LYStick, 0, 255, -127, 127);
  rightxJoystickValue = map(RXStick, 0, 255, -127, 127);
  rightyJoystickValue = map(RYStick, 0, 255, -127, 127);


  gp.setLeftXaxis(leftxJoystickValue);
  gp.setRightXaxis(rightxJoystickValue);
  gp.setLeftYaxis(leftyJoystickValue);
  gp.setRightYaxis(rightyJoystickValue);

  delay(20);
}
