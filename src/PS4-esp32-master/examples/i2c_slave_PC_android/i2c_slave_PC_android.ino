/*
  ANDROID GAMEPAD
  {A=1, B=2, C=3, X=4, Y=5, Z=6, L1=7, R1=8, L2=9, R2=10,
  Select=11, Start=12, PS=13, L3=14 , R3=15}

  PS GAMEPAD MODE
  {SQUARE=1, X=2, CIRCLE=3, TRIANGLE=4, L1=5, R1=6, L2=7, R2=8,
  Select=9, Start=10, L3=11, R3=12, PS=13}

*/
// Include Arduino Wire library for I2C
#include <Wire.h>

#include <Arduino.h>
#include <BleGamepad.h>

#define NUM_BUTTONS 14

// Define Slave I2C Address
#define SLAVE_ADDR 9

//There is not buttons for Y and Z
int androidGamepadButtons[NUM_BUTTONS] = {2, 3, 4, 1, 6, 8, 5, 7, 10, 9, 13, 12, 11, 14};
int PCGamepadButtons[NUM_BUTTONS] = {1, 2, 4, 3, 6, 8, 5, 7, 10, 9, 0, 12, 11};

/*
  int Cross = 0;
  int Circle = 0;
  int Triangle = 0;
  int Square = 0;
  int R1 = 0;
  int R2 = 0;
  int L1 = 0;
  int L2 = 0;
  int Options = 0;
  int Share = 0;
  int PS_home = 0;
  int R3 = 0;
  int L3 = 0;
  int TouchPad = 0;
*/
int RXStick = 0;
int RYStick = 0;
int LXStick = 0;
int LYStick = 0;

uint16_t leftxJoystickValue = 0;
uint16_t leftyJoystickValue = 0;
uint16_t rightxJoystickValue = 0;
uint16_t rightyJoystickValue = 0;

typedef enum {ANDROID, PC} GamepadModes;
GamepadModes gamepadMode = ANDROID;

BleGamepad bleGamepad("Mike Gamepad", "Mike Home");
BleGamepadConfiguration bleGamepadConfig;

byte Data[18];
/////////////////////////////////////////////////////////////////////////////
void setup() {


  bleGamepadConfig.setAutoReport(false);
  bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD); // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
  bleGamepadConfig.setVid(0xe502);
  bleGamepadConfig.setPid(0xabcd);
  bleGamepadConfig.setHatSwitchCount(4);
  bleGamepad.begin(&bleGamepadConfig);

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

///////////////////////////////////////////////////////////////

void loop() {
  // put your main code here, to run repeatedly:


  if (bleGamepad.isConnected()) {
    //Joysticks lecture



    //Compute joysticks value

    LXStick = Data[14];
    LYStick = Data[15];
    RXStick = Data[16];
    RYStick = Data[17];

    leftxJoystickValue = map(LXStick, 0, 255, 0, 32737);
    leftyJoystickValue = map(LYStick, 0, 255, 32737, 0);
    rightxJoystickValue = map(RXStick, 0, 255, 0, 32737);
    rightyJoystickValue = map(RYStick, 0, 255, 32737, 0);


    switch (gamepadMode) {
      case ANDROID:
        for (int i = 0; i < NUM_BUTTONS; i++) {
          if (Data[i] == 1) {
            bleGamepad.press(androidGamepadButtons[i]);
          }
          else {
            bleGamepad.release(androidGamepadButtons[i]);
          }
          joysticksHandlerForMobile(leftxJoystickValue, leftyJoystickValue, rightxJoystickValue, rightyJoystickValue);
        }
        break;

        case PC:
        for (int i = 0; i < NUM_BUTTONS; i++) {
          if (Data[i] == 1) {
            bleGamepad.press(androidGamepadButtons[i]);
          }
          else {
            bleGamepad.release(androidGamepadButtons[i]);
          }
          joysticksHandlerForPC(leftxJoystickValue, leftyJoystickValue, rightxJoystickValue, rightyJoystickValue);
        }
        break;

        /*      case PC:
                for (int i = 0; i < NUM_BUTTONS; i++) {
                  if (!digitalRead(buttonsPins[i])) {
                    bleGamepad.press(PCGamepadButtons[i]);
                  }
                  else {
                    bleGamepad.release(PCGamepadButtons[i]);
                  }
                  joysticksHandlerForPC(leftVrxJoystickValue, leftVryJoystickValue, rightVrxJoystickValue, rightVryJoystickValue);
                }
                break;     */
    }

    bleGamepad.sendReport();
  }
}

void joysticksHandlerForMobile(uint16_t leftx, uint16_t lefty, uint16_t rightx, uint16_t righty) {
  bleGamepad.setLeftThumb(leftx, leftyJoystickValue);
  bleGamepad.setRightThumb(rightxJoystickValue, rightyJoystickValue);
//  Serial.print("LXStick ");
//  Serial.println(leftxJoystickValue);
//  Serial.print("LYStick ");
//  Serial.println(leftyJoystickValue);
//  Serial.print("RXStick ");
//  Serial.println(rightxJoystickValue);
//  Serial.print("RYStick ");
//  Serial.println(rightyJoystickValue);

}

void joysticksHandlerForPC(uint16_t leftx, uint16_t lefty, uint16_t rightx, uint16_t righty) {
  bleGamepad.setX(leftxJoystickValue);
  bleGamepad.setY(leftyJoystickValue);
  bleGamepad.setZ(rightxJoystickValue);
  bleGamepad.setRX(rightyJoystickValue);
}
