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
int rightGamepadButtons[NUM_BUTTONS] = {2, 3, 4, 1, 6, 8, 0, 0, 10, 0, 13, 12, 0, 14};
int leftGamepadButtons[NUM_BUTTONS] = {0, 0, 0, 0, 5, 7, 0, 0, 9, 0, 13, 11, 0, 14};

// int androidGamepadButtons[NUM_BUTTONS] = {X, O, Δ, ■, R1, R2, L1, L2, OPTIONS, SHARE, PS, R3, L3, TOUCHPAD};

// int PCGamepadButtons[NUM_BUTTONS] = {1, 2, 4, 3, 6, 8, 5, 7, 10, 9, 0, 12, 11};

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

int Enable = 0;
int Side = 0;


int LED_enb = 27;
int LED_right = 25;
int LED_left = 26;

BleGamepad bleGamepad("Mike Gamepad", "Mike Home");
BleGamepadConfiguration bleGamepadConfig;

byte Data[24];

unsigned long startTime;
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

  pinMode(LED_enb, OUTPUT);
  pinMode(LED_right, OUTPUT);
  pinMode(LED_left, OUTPUT);
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
  delay(50);

  if (bleGamepad.isConnected()) {
    startTime = millis();

    int Side = Data[22];
    int Enable = Data[23];

    //Joysticks lecture
    LXStick = Data[18];
    LYStick = Data[19];
    RXStick = Data[20];
    RYStick = Data[21];

    leftxJoystickValue = map(LXStick, 0, 255, 0, 32737);
    leftyJoystickValue = map(LYStick, 0, 255, 32737, 0);
    rightxJoystickValue = map(RXStick, 0, 255, 0, 32737);
    rightyJoystickValue = map(RYStick, 0, 255, 32737, 0);
    switch (Enable) {
      case 0: ///////////////////////////// Adaptation disabled
        digitalWrite(LED_enb, LOW);
        digitalWrite(LED_right, LOW);
        digitalWrite(LED_left, LOW);
        for (int i = 0; i < NUM_BUTTONS; i++) {
          if (Data[i] == 1) {
            Serial.println(androidGamepadButtons[i]);
            bleGamepad.press(androidGamepadButtons[i]);
          }

          joysticksHandlerForMobile(leftxJoystickValue, leftyJoystickValue, rightxJoystickValue, rightyJoystickValue);
        }

        if (Data[14] == 1) {
          bleGamepad.setHat4(DPAD_UP);
        }
        if (Data[15] == 1) {
          bleGamepad.setHat4(DPAD_LEFT);
        }
        if (Data[16] == 1) {
          bleGamepad.setHat4(DPAD_RIGHT);
        }
        if (Data[17] == 1) {
          bleGamepad.setHat4(DPAD_DOWN);
        }

        break;


      case 1: ///////////////////////// Adaptation enabled
        digitalWrite(LED_enb, HIGH);
        if (Side == 0) {   //////////////////Left side working
          digitalWrite(LED_left, HIGH);
          digitalWrite(LED_right, LOW);

          for (int i = 0; i < NUM_BUTTONS; i++) {
            bleGamepad.release(leftGamepadButtons[i]);
          }

          for (int i = 0; i < NUM_BUTTONS; i++) {
            if (Data[i] == 1) {
              bleGamepad.press(leftGamepadButtons[i]);
            }

            joysticksHandlerForMobile(rightxJoystickValue, rightyJoystickValue, 16368, 16368);
          }

          if (Data[2] == 1) {
            bleGamepad.setHat4(DPAD_UP);
          }
          if (Data[3] == 1) {
            bleGamepad.setHat4(DPAD_LEFT);
          }
          if (Data[1] == 1) {
            bleGamepad.setHat4(DPAD_RIGHT);
          }
          if (Data[0] == 1) {
            bleGamepad.setHat4(DPAD_DOWN);
          }
        }



        if (Side == 1) {   ////////////////////////////Right side working
          digitalWrite(LED_right, HIGH);
          digitalWrite(LED_left, LOW);
          for (int i = 0; i < NUM_BUTTONS; i++) {
            if (Data[i] == 1) {
              bleGamepad.press(rightGamepadButtons[i]);
            }

            joysticksHandlerForMobile(16368, 16368, rightxJoystickValue, rightyJoystickValue);
          }
        }

        break;

    }
    bleGamepad.sendReport();

    for (int i = 0; i < NUM_BUTTONS; i++) {
      bleGamepad.release(androidGamepadButtons[i]);
    }

    bleGamepad.setHat4();

    unsigned long endTime = millis(); // Guarda el tiempo actual como tiempo de finalización
    unsigned long elapsedTime = endTime - startTime; // Calcula el tiempo transcurrido
    Serial.print("elapsed Time ");
    Serial.println(elapsedTime);
  }
}

void joysticksHandlerForMobile(uint16_t leftx, uint16_t lefty, uint16_t rightx, uint16_t righty) {
  bleGamepad.setLeftThumb(leftx, lefty);
  bleGamepad.setRightThumb(rightx, righty);

}

void joysticksHandlerForPC(uint16_t leftx, uint16_t lefty, uint16_t rightx, uint16_t righty) {
  bleGamepad.setX(leftx);
  bleGamepad.setY(lefty);
  bleGamepad.setZ(rightx);
  bleGamepad.setRX(righty);
}
