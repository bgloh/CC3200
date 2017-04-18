#include "pwm.h"

// instantiation of a Timer object
// 32 bit timer 
Timer timerA2(TIMERA2_BASE,TIMER_BOTH);

void setup()
{
  // put your setup code here, to run once:
  setupTimerForOverflowInterrupt(); // setup timer for overflow interrupt
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
 
}

void setupTimerForOverflowInterrupt()
{
  // timerA2PWM.pinMuxConfigure(2, PIN_64, PIN_MODE_3);
  timerA2.clockConfigure(PRCM_TIMERA2);
  timerA2.configure(TIMER_CFG_PERIODIC ); // full width, concatenated timer (TIMER_A + TIMER_B)
  timerA2.setInterrupt(TIMERA2_BASE,TIMER_BOTH,TIMER_TIMA_TIMEOUT | TIMER_TIMB_TIMEOUT,timerOverflowISR);
  timerA2.setPeriod(100);   //    period in milisecond
  timerA2.enable();         //     enable timer
}
void timerOverflowISR()
{
  static unsigned long count;
  unsigned long ulstatus,timerValue;
  count++;
  ulstatus = timerA2.intStatus(TIMERA2_BASE);
  timerValue = timerA2.valueGet(TIMERA2_BASE,TIMER_BOTH);
  timerA2.intClear(TIMERA2_BASE, ulstatus);
  Serial.print("ISR COUNTER: ");
  Serial.println(count);
}



