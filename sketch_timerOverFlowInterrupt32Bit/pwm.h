//*****************************************************************************
// pwm.h
// 6.29.2016
// by Dr. Byoung Loh
// function prototype for pwm
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
//*****************************************************************************


#include "Energia.h"
#include "inc\hw_memmap.h"
#include "inc\hw_types.h"
#include "inc\hw_ints.h"
#include "driverlib\debug.h"
#include "driverlib\interrupt.h"
#include "driverlib\timer.h"
#include "driverlib\rom.h"
#include "driverlib\rom_map.h"
#include "driverlib\timer.h"
#include "driverlib\utils.h"
#include "driverlib\prcm.h"
#include "driverlib\pin.h"

class Timer {
  private:
    unsigned long _ulBase; // TIMER_BASE
    unsigned long _ulTimer; // TIMER
    unsigned char _preScale ;
    unsigned char _inversion ;
    unsigned long _timerIntervalReload;
    unsigned long _matchSetValue;
  //  void (*intCallBack)();
  
  public: 
   unsigned long timerIntervalReload;
   //unsigned long  matchSetValue;
   Timer(unsigned long ulBase, unsigned long ulTimer); // Constructor
   unsigned long getTimerIntervalReload(void); //getter method 
   unsigned long getMatchSetValue(void); //getter method 

   void configure(unsigned long ulConfig); //Configure timer
   void prescaleSet(); // configure clock scale
   void controlLevel(); //inverting the timer output if required
   void setPeriod(float fPeriod);  // Set timer period in mili-second
   void setDuty(float fDuty);     // Set timer duty in mili-second
   void matchSet(unsigned long matchSetValue); // Match value set to reflect duty cycle
   void enable(void); // Enable Timer 
   void pinMuxConfigure(unsigned char ucTimer, unsigned char ucPin, unsigned char ucPinMode); // Configure pin mux
   void clockConfigure (unsigned long ulPRCM_Timer); // Configure clock
   void updateDutyCycle(unsigned long dutyCycle);  // Update duty cycle
   // Interrupt
   void setInterrupt(unsigned long ulBase, unsigned long ulTimer,  unsigned long ulEvent, void (*intCallBack)());
   void setCallBack( unsigned long ulBase, unsigned long ulTimer, void (*intCallBack)() );
   unsigned long intStatus(unsigned long ulBase);
   void intClear(unsigned long ulBase, unsigned long ulflag);
   void intEnable(unsigned long ulBase, unsigned long ulflag);
   unsigned long valueGet(unsigned long ulBase, unsigned long ulTimer);
   

 };
