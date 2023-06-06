#include <Wire.h>
#include "UsbKeyboard.h"
uint8_t buf[8] = { 0 }; //Keyboard report buffer
//_____________________________________________________-

#define KEY_LEFT_CTRL  0x80
#define KEY_LEFT_SHIFT 0x81
#define KEY_LEFT_ALT   0x82
#define KEY_LEFT_GUI   0x83
#define KEY_RIGHT_CTRL 0x84
#define KEY_RIGHT_SHIFT    0x85
#define KEY_RIGHT_ALT  0x86
#define KEY_RIGHT_GUI  0x87

#define KEY_UP_ARROW   0xDA
#define KEY_DOWN_ARROW 0xD9
#define KEY_LEFT_ARROW 0xD8
#define KEY_RIGHT_ARROW    0xD7
#define KEY_BACKSPACE  0xB2
#define KEY_TAB        0xB3
#define KEY_RETURN 0xB0
#define KEY_ESC        0xB1
#define KEY_INSERT 0xD1
#define KEY_DELETE 0xD4
#define KEY_PAGE_UP    0xD3
#define KEY_PAGE_DOWN  0xD6
#define KEY_HOME   0xD2
#define KEY_END        0xD5
#define KEY_CAPS_LOCK  0xC1
#define KEY_F1     0xC2
#define KEY_F2     0xC3
#define KEY_F3     0xC4
#define KEY_F4     0xC5
#define KEY_F5     0xC6
#define KEY_F6     0xC7
#define KEY_F7     0xC8
#define KEY_F8     0xC9
#define KEY_F9     0xCA
#define KEY_F10        0xCB
#define KEY_F11        0xCC
#define KEY_F12        0xCD

//_____________________________________________________-


//#include "KeyboardController.h"
//#include "Keyboard.h"
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
//  Serial.begin(115200);
  Serial.begin(9600);
  Serial.println("USB keyboard");

  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);

  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
  Wire.setClock(100000);

//  Mouse.begin();
//  Keyboard.begin();


}

void receiveEvent(int len) {
  for (int i = 0; i < len; i++)
  {
    Data[i] = Wire.read();
  }
}

/////////////////////////////////////////////////

void loop() {

    UsbKeyboard.update();
/*
  LXStick = Data[14];
  LYStick = Data[15];
  RXStick = Data[16];
  RYStick = Data[17];

  leftxJoystickValue = map(LXStick, 0, 255, -128, 128);
  leftyJoystickValue = map(LYStick, 0, 255, -128, 128);
  rightxJoystickValue = map(RXStick, 0, 255, -128, 128);
  rightyJoystickValue = map(RYStick, 0, 255, -128, 128);
*/
//  Serial.print("left X ");
//  Serial.println(leftxJoystickValue);
//  Serial.print("left Y ");
//  Serial.println(leftyJoystickValue);

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

 /* if (leftyJoystickValue > 15) {
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
*/
  //Keyboard.press(KEY_RIGHT_ARROW);
  //delay (500);
  //Keyboard.release(KEY_RIGHT_ARROW);
  //delay (500);AAAAAAAAAAAAA
  //Keyboard.press(KEY_LEFT_ARROW);
  //delay (500);
  //Keyboard.release(KEY_LEFT_ARROW);
  //delay (500);

//Keyboard.write(69);         // sends ASCII value 69, or E
//delay (500);
//Keyboard.write(0x0D);         // sends ASCII value 65, or A
//delay (500);
//Keyboard.write(0X4D);         // sends ASCII value 65, or A
//delay (500);
//Keyboard.write('C');            // same thing as a quoted character C
//delay (500);
//Keyboard.write(0x31);       // same thing in hexadecimal 1
//delay (500);
//Keyboard.write(97);       // sends ASCII value 97, or a
//delay (500);
//Keyboard.write(219);       // same thing in hexadecimal cuadrado negro
//delay (500);
//Keyboard.write(0b01000001); // same thing in binary (weird choice, but it works A)
//delay (500);
//Keyboard.println("Hola mundo!");
//delay (500);
//Keyboard.write(0xD7);   //derecha
//delay (1500);
//Keyboard.write(0xD8);   //izquierda
//delay (1500);
//Keyboard.write(0xB0);   //return
//delay (500);
//  Serial.print("NO FORMAT");  // prints a label
//  Serial.print("\t");         // prints a tab
//delay (500);
//  Serial.print("DEC");
//  Serial.print("\t");
//delay (500);
//  Serial.print("HEX");
//  Serial.print("\t");
//delay (500);
//  Serial.print("OCT");
//  Serial.print("\t");
//delay (500);
//  Serial.print("BIN");
//  Serial.println();        // carriage return after the last label
//delay (500);

buf[2] = 26;
Serial.write(buf,8);
releaseKey();
delay (500);

buf[2] = 4;
Serial.write(buf,8);
releaseKey();
delay (500);

buf[2] = 22;
Serial.write(buf,8);
releaseKey();
delay (500);

buf[2] = 7;
Serial.write(buf,8);
releaseKey();
delay (500);


  
//  Serial.write(0xB0);
//  Serial.print(char(176));
//  
//  Serial.print(char(215));
//  Serial.print(0xD7,10);       //Derecha
//  Keyboard.releaseAll();
//  delay (500);
//  Serial.print(0xD8,10);       //Izquierda
//  Keyboard.releaseAll();
//------------------------------------------
    UsbKeyboard.sendKeyStroke(KEY_H);
    UsbKeyboard.sendKeyStroke(KEY_E);
    UsbKeyboard.sendKeyStroke(KEY_L);
    UsbKeyboard.sendKeyStroke(KEY_L);
    UsbKeyboard.sendKeyStroke(KEY_O);

    UsbKeyboard.sendKeyStroke(KEY_SPACE);

    UsbKeyboard.sendKeyStroke(KEY_W);
    UsbKeyboard.sendKeyStroke(KEY_O);
    UsbKeyboard.sendKeyStroke(KEY_R);
    UsbKeyboard.sendKeyStroke(KEY_L);
    UsbKeyboard.sendKeyStroke(KEY_D);
    //UsbKeyboard.sendKeyStroke(KEY_B, MOD_GUI_LEFT);

    UsbKeyboard.sendKeyStroke(KEY_ENTER);
delay(200);




//------------------------------------------
}

// Function for Key Release

void releaseKey() {

buf[0] = 0;

buf[2] = 0;

Serial.write(buf, 8); // Send Release key

}
