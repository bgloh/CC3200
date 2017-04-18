//*****************************************************************************
// pwm.cpp
//
// configure the device pins for different peripheral signals
// 6.29.2016
// by Dr. Byoung Loh
// function definition for pwm

// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// // The PWM works based on the following settings:
//     Timer reload interval -> determines the time period of one cycle
//     Timer match value -> determines the duty cycle 
//                          range [0, timer reload interval]
// The computation of the timer reload interval and dutycycle granularity
// is as described below:
// Timer tick frequency = 80 Mhz = 80000000 cycles/sec
// For a time period of 0.5 ms, 
//      Timer reload interval = 80000000/2000 = 40000 cycles
// To support steps of duty cycle update from [0, 255]
//      duty cycle granularity = ceil(40000/255) = 157
// Based on duty cycle granularity,
//      New Timer reload interval = 255*157 = 40035
//      New time period = 0.5004375 ms
//      Timer match value = (update[0, 255] * duty cycle granularity)
//*********************************************************************

#include "pwm.h"
#define TIMER_TICK              80000000UL    // 80 MHz = 8000000 cycles / sec 
#define INVERSION_YES            0            // PWM SIGNAL INVERSION
#define INVERSION_NO             1
//#define TIMER_INTERVAL_RELOAD   40035 /* =(255*157) */
//#define DUTYCYCLE_GRANULARITY   157

// Constructor
// fPeriod : period in ms, fDuty : Duty in ms
Timer::Timer(unsigned long ulBase, unsigned long ulTimer)
{
  
  _ulBase = ulBase;
  _ulTimer = ulTimer;
  _preScale = 0 ;
  _inversion = INVERSION_YES ;
  _timerIntervalReload = TIMER_TICK / 1000;  // default period     : 1 ms
  _matchSetValue = _timerIntervalReload / 2 ; // defualt duty cyle   : 50 %
 }

unsigned long Timer::getTimerIntervalReload(void)
{
     return _timerIntervalReload;
}

unsigned long Timer::getMatchSetValue(void)
{
     return _matchSetValue;
}

   void Timer::configure(unsigned long ulConfig)
{
  //Configure timer  ;
  TimerConfigure(_ulBase, ulConfig);
  //inverting the timer output if required
  TimerControlLevel(_ulBase, _ulTimer, _inversion); 

} 

void Timer::prescaleSet()
{
  // configure clock scale
  TimerPrescaleSet(_ulBase, _ulTimer, _preScale);
}

void Timer::controlLevel()
{
  //inverting the timer output if required
  TimerControlLevel(_ulBase, _ulTimer, _inversion);
} 
  // Set timer period in mili-second
void Timer::setPeriod(float fPeriod)
{
  unsigned long periodCount;
  periodCount = (TIMER_TICK * fPeriod /1000);
  _timerIntervalReload = periodCount;
  // Set max. timer counter value
  TimerLoadSet(_ulBase, _ulTimer, _timerIntervalReload);
}

// Set Duty in mili-second
void Timer::setDuty(float fDuty)
{
  unsigned long dutyCount;
  dutyCount = (TIMER_TICK * fDuty /1000);
  _matchSetValue = dutyCount & 0x0000FFFF;
  _preScale = dutyCount >> 16;
  TimerPrescaleMatchSet(_ulBase, _ulTimer, _preScale);
  TimerMatchSet(_ulBase, _ulTimer, _matchSetValue);
}

void Timer::matchSet(unsigned long matchSetValue)
{
  // Match value set to reflect duty cycle
  _matchSetValue = matchSetValue;
  TimerMatchSet(_ulBase, _ulTimer, _matchSetValue);
}

void Timer::enable()  
{
  // Enable Timer
  TimerEnable(_ulBase, _ulTimer);
}
// Configure clock
void Timer::clockConfigure (unsigned long ulPRCM_Timer)
{
  // Enable clock to peripheral
 // if (ucTimer == 2)
  PRCMPeripheralClkEnable(ulPRCM_Timer, PRCM_RUN_MODE_CLK);
}
// Configure pin mux
void Timer::pinMuxConfigure(unsigned char ucTimer, unsigned char ucPin, unsigned char ucPinMode)
{
  
  // Configure PIN_64 for TIMER PWM5 GT_PWM05
  PinTypeTimer(PIN_64, PIN_MODE_3);   
}
  
 // Update duty cycle
 void Timer::updateDutyCycle(unsigned long dutyCycle)
{
  TimerMatchSet(_ulBase,_ulTimer,dutyCycle);
}

// Interrupt


void Timer::setInterrupt(unsigned long ulBase, unsigned long ulTimer,  unsigned long ulEvent,void (*intCallBack)())
{
  unsigned long ulstatus;  
  TimerControlEvent( ulBase, ulTimer, TIMER_EVENT_POS_EDGE);
  TimerIntRegister(ulBase, ulTimer, intCallBack);
  TimerIntEnable(ulBase, ulEvent);
 // HWREG(0x4032008) |= (1<<10);
 }


void Timer::setCallBack(unsigned long ulBase, unsigned long ulTimer, void (*intCallBack)())
{
  unsigned long   ulIntFlags = TIMER_CAPB_EVENT ;  
  TimerIntRegister  ( ulBase,  ulTimer,  intCallBack);
    TimerIntEnable  ( ulBase,  ulIntFlags);
    IntPrioritySet(INT_TIMERA0B, INT_PRIORITY_LVL_7);
}

unsigned long Timer::intStatus(unsigned long ulBase)
{
  unsigned long ulstatus;
  ulstatus = TimerIntStatus(ulBase,true);
  return ulstatus;
}
void Timer::intClear(unsigned long ulBase, unsigned long ulflag)
{
  TimerIntClear(ulBase, ulflag);
 }
 
 void Timer::intEnable(unsigned long ulBase, unsigned long ulflag)
{
  TimerIntEnable(ulBase,ulflag);
}
unsigned long Timer::valueGet(unsigned long ulBase, unsigned long ulTimer)
{
  unsigned long timerValue;
  timerValue = TimerValueGet(ulBase,ulTimer);
  return timerValue ;
}
   





