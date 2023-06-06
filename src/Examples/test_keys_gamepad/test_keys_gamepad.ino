/*
  ANDROID GAMEPAD
  {A=1, B=2, C=3, X=4, Y=5, Z=6, L1=7, R1=8, L2=9, R2=10,
  Select=11, Start=12, PS=13, L3=14 , R3=15}

  PS GAMEPAD MODE
  {SQUARE=1, X=2, CIRCLE=3, TRIANGLE=4, L1=5, R1=6, L2=7, R2=8,
  Select=9, Start=10, L3=11, R3=12, PS=13}

*/

#include <Arduino.h>
#include <BleGamepad.h>

#define NUM_BUTTONS 30

//There is not buttons for Y and Z
int test_buttons[NUM_BUTTONS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
int androidGamepadButtons[NUM_BUTTONS] = {1, 2, 3, 4, 8, 10, 7, 9, 12, 11, 13, 15, 14};
int PCGamepadButtons[NUM_BUTTONS] = {1, 2, 4, 3, 6, 8, 5, 7, 10, 9, 0, 12, 11};


BleGamepad bleGamepad("Mike Gamepad", "Mike Center");
BleGamepadConfiguration bleGamepadConfig;


void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);

  bleGamepadConfig.setAutoReport(false);
  bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD); // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
  bleGamepadConfig.setVid(0xe502);
  bleGamepadConfig.setPid(0xabcd);
  bleGamepadConfig.setHatSwitchCount(4);
  bleGamepad.begin(&bleGamepadConfig);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bleGamepad.isConnected()) {

    for (int i = 0; i < NUM_BUTTONS; i++) {

      bleGamepad.press(test_buttons[i]);
      bleGamepad.sendReport();
      Serial.println(test_buttons[i]);
      delay(1000);

      bleGamepad.release(test_buttons[i]);
      bleGamepad.sendReport();
      delay(500);
    }

    bleGamepad.sendReport();
  }
}
