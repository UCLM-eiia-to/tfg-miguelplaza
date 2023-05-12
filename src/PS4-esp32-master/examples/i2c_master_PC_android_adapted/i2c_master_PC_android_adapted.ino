// Include Arduino Wire library for I2C
#include <Wire.h>
#include <PS4Controller.h>

#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_err.h"

// Define Slave I2C Address
#define SLAVE_ADDR 9

// Integer to hold potentiometer value
int Square = 0;
int Cross = 0;
int Circle = 0;
int Triangle = 0;
int L1 = 0;
int R1 = 0;
int L2 = 0;
int R2 = 0;
int Share = 0;
int Options = 0;
int L3 = 0;
int R3 = 0;
int PS_home = 0;
int TouchPad = 0;

int Up = 0;
int Left = 0;
int Right = 0;
int Down = 0;

int RXStick = 0;
int RYStick = 0;
int LXStick = 0;
int LYStick = 0;
int leftxJoystickValue = 0;
int leftyJoystickValue = 0;
int rightxJoystickValue = 0;
int rightyJoystickValue = 0;

int Side = 0;
int Enable = 1;
int Enable_button = 2;
int Side_button = 27;

void setup() {

  // Initialize I2C communications as Master
  Wire.begin();

  Serial.begin(115200);

  // PS4.begin("28:66:e3:3b:75:ea");
  PS4.begin("28:66:e3:3b:75:ea");

  uint8_t pairedDeviceBtAddr[20][6];
  int count = esp_bt_gap_get_bond_device_num();
  esp_bt_gap_get_bond_device_list(&count, pairedDeviceBtAddr);
  for (int i = 0; i < count; i++)
  {
    esp_bt_gap_remove_bond_device(pairedDeviceBtAddr[i]);
  }

  Serial.println("Ready.");
  Wire.setClock(100000);

  pinMode(Enable_button, INPUT_PULLUP);
  pinMode(Side_button, INPUT_PULLUP);
}

void loop() {
  if (PS4.isConnected())
  {
    int Enable_value = digitalRead(Enable_button);
    int Side_value = digitalRead(Side_button);

    if (Enable_value == 0) {
      Enable = !Enable; // Invertimos el valor de la variable
      delay(500); // Esperamos un tiempo para evitar lecturas múltiples del pulsador
    }
    if (Side_value == 0) {
      Side = !Side; // Invertimos el valor de la variable
      delay(500); // Esperamos un tiempo para evitar lecturas múltiples del pulsador
    }

    delay(25);
    Cross = PS4.Cross();
    Circle = PS4.Circle();
    Triangle = PS4.Triangle();
    Square = PS4.Square();
    L1 = PS4.L1();
    R1 = PS4.R1();
    L2 = PS4.L2();
    R2 = PS4.R2();
    Share = PS4.Share();
    Options = PS4.Options();
    L3 = PS4.L3();
    R3 = PS4.R3();
    PS_home = PS4.PSButton();
    TouchPad = PS4.Touchpad();
    Up = PS4.Up();
    Left = PS4.Left();
    Right = PS4.Right();
    Down = PS4.Down();

    RXStick = PS4.RStickX();
    RYStick = PS4.RStickY();
    LXStick = PS4.LStickX();
    LYStick = PS4.LStickY();

    leftxJoystickValue = map(LXStick, -128, 128, 0, 255);
    leftyJoystickValue = map(LYStick, -128, 128, 0, 255);
    rightxJoystickValue = map(RXStick, -128, 128, 0, 255);
    rightyJoystickValue = map(RYStick, -128, 128, 0, 255);

    // Write a charatre to the Slave
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(Cross);
    Wire.write(Circle);
    Wire.write(Triangle);
    Wire.write(Square);
    Wire.write(R1);
    Wire.write(R2);
    Wire.write(L1);
    Wire.write(L2);
    Wire.write(Options);
    Wire.write(Share);
    Wire.write(PS_home);
    Wire.write(R3);
    Wire.write(L3);
    Wire.write(TouchPad);
    
    Wire.write(Up);
    Wire.write(Left);
    Wire.write(Right);
    Wire.write(Down);


    Wire.write(leftxJoystickValue);
    //Serial.print("LXStick ");
    //Serial.println(leftxJoystickValue);

    Wire.write(leftyJoystickValue);
    //Serial.print("LYStick ");
    //Serial.println(leftyJoystickValue);

    Wire.write(rightxJoystickValue);
    // Serial.print("RXStick ");
    //   Serial.println(rightxJoystickValue);

    Wire.write(rightyJoystickValue);
    //    Serial.print("RYStick ");
    //    Serial.println(rightyJoystickValue);

    Wire.write(Side);
    Wire.write(Enable);

    Wire.endTransmission();
  }


}
