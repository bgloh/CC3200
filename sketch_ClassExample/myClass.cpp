#include "Arduino.h"
#include "myClass.h"

myClass::myClass(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void myClass::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void myClass::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
