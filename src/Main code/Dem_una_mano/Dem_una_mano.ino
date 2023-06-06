#include <PS4Controller.h>

int ledPins[] = {4, 0, 2, 15, 32, 33, 25, 26, 27, 14};

int inputPin = 23; // El número del pin al que está conectado el sensor de entrada

int enableMotor = 22;
int MotorPin1 = 12;
int MotorPin2 = 13;

int MotorSpeed;
const int PWMFreq = 10; /* 5 KHz */
const int PWMResolution = 3;
const int MotorPWMSpeedChannel = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(inputPin, INPUT_PULLUP); // Configura el pin de entrada como una entrada con resistencia pull-up

  for (int i = 0; i < 10; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  PS4.begin("b4:8a:0a:82:bd:5e");
  Serial.println("Ready.");

  pinMode(enableMotor, OUTPUT);
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);

  ledcSetup(MotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcAttachPin(enableMotor, MotorPWMSpeedChannel);
  rotateMotor(0);
}

void loop()
{
  // Below has all accessible outputs from the controller
  if (PS4.isConnected())
  {
    int buttonState = digitalRead(inputPin); // Lee el estado del botón

    switch (buttonState) {
      case LOW:
        digitalWrite(ledPins[0], PS4.Square());
        digitalWrite(ledPins[1], PS4.Cross());
        digitalWrite(ledPins[2], PS4.Circle());
        digitalWrite(ledPins[3], PS4.Triangle());

        MotorSpeed = map( PS4.RStickY(), -127, 127, -8, 8);
        MotorSpeed = constrain(MotorSpeed, -8, 8);
        rotateMotor(MotorSpeed);
        break;

      case HIGH:
        digitalWrite(ledPins[5], PS4.Square());
        digitalWrite(ledPins[6], PS4.Cross());
        digitalWrite(ledPins[7], PS4.Circle());
        digitalWrite(ledPins[8], PS4.Triangle());
        break;
    }
  }
}

void rotateMotor(int MotorSpeed)
{

  if (MotorSpeed < -2)
  {
    digitalWrite(MotorPin1, LOW);
    digitalWrite(MotorPin2, HIGH);

  }
  else if (MotorSpeed > 2)
  {
    digitalWrite(MotorPin1, HIGH);
    digitalWrite(MotorPin2, LOW);
    Serial.println(MotorSpeed);
  }
  else
  {
    digitalWrite(MotorPin1, LOW);
    digitalWrite(MotorPin2, LOW);
  }
  ledcWrite(MotorPWMSpeedChannel, abs(MotorSpeed));

}
