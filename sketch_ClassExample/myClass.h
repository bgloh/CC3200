
#ifndef myClass_h
#define myClass_h
#include "Arduino.h"

class myClass
{
  public:
   myClass(int pin);
   void dot();
   void dash();
   int id = 3; 
  private:
   int _pin;
};

#endif

