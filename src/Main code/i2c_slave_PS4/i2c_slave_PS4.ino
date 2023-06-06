#include <Wire.h>

#include "Keyboard.h"
//#include "Mouse.h"


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


///////////////////////////////////////////////////////////////////////
void setup() {

  // Setup Serial Monitor
  Serial.begin(57600);
  Serial.println("USB keyboard");

  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);

  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
  Wire.setClock(100000);

//  Mouse.begin();
  Keyboard.begin();


}

void receiveEvent(int len) {
  for (int i = 0; i < len; i++)
  {
    Data[i] = Wire.read();
  }
}

/////////////////////////////////////////////////

void loop() {

  LXStick = Data[14];
  LYStick = Data[15];
  RXStick = Data[16];
  RYStick = Data[17];

  leftxJoystickValue = map(LXStick, 0, 255, -128, 128);
  leftyJoystickValue = map(LYStick, 0, 255, -128, 128);
  rightxJoystickValue = map(RXStick, 0, 255, -128, 128);
  rightyJoystickValue = map(RYStick, 0, 255, -128, 128);

  Serial.print("left X ");
  Serial.println(leftxJoystickValue);
  Serial.print("left Y ");
  Serial.println(leftyJoystickValue);

  /*
    if (rightxJoystickValue > 15) {
      Mouse.move(2, 0);
    }
    if (rightxJoystickValue < -15) {
      Mouse.move(-2, 0);
    }
    if (rightyJoystickValue > 15) {
      Mouse.move(0, -2);
    }
    if (rightyJoystickValue < -15) {
      Mouse.move(0, 2);
    }
  */

  if (leftyJoystickValue > 15) {
    //  Keyboard.write('w');
  }
  if (leftyJoystickValue < -15) {
    //  Keyboard.write('s');
  }
  if (leftxJoystickValue > 15) {
    //  Keyboard.write('d');
    //Keyboard.write(KEY_RIGHT_ARROW);
  }
  if (leftxJoystickValue < -15) {
    //  Keyboard.write('a');
    //Keyboard.write(KEY_LEFT_ARROW);
  }


  Keyboard.write(KEY_RIGHT_ARROW);
  Keyboard.release(KEY_RIGHT_ARROW);
  //delay(1000);
  //Keyboard.press(KEY_LEFT_ARROW);
 //Keyboard.release(KEY_LEFT_ARROW);
  delay(100);
    Keyboard.write(KEY_LEFT_ARROW);
    Keyboard.release(KEY_LEFT_ARROW);
    delay(100);
}
