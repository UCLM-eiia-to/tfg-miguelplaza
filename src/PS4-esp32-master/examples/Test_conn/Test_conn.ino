#include <PS4Controller.h>

int ledPins[] = {4, 0, 2, 15, 32, 33, 25, 26, 27, 14};

int ledLectura = 0;

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < 10; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  PS4.begin("b4:8a:0a:82:bd:5e");
  Serial.println("Ready.");
}

void loop()
{
  // Below has all accessible outputs from the controller
  if (PS4.isConnected())
  {
    ledLectura = PS4.R2Value();
    float LedOn = ledLectura / 25.5;
    int int_LedOn = int(LedOn);
    Serial.printf("R2 button at %d\n", PS4.R2Value());
    if (ledLectura > 0)
    {
      for (int i = 0; i < int_LedOn; i++)
      {
        digitalWrite(ledPins[i], HIGH);
      }
      for (int i = int_LedOn; i < 10; i++)
      {
        digitalWrite(ledPins[i], LOW);
      }
    }

    if (ledLectura == 0) {
      for (int i = 0; i < 10; i++)
      {
        digitalWrite(ledPins[i], LOW);
      }
    }


    // This delay is to make the output more human readable
    // Remove it when you're not trying to see the output
    delay(100);
  }
}
