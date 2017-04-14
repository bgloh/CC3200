
// CO2 Meter Amphenol T6713 i2c Example Interface

// By Marv Kausch, 12/2016 at CO2 Meter <co2meter.com>
// Talks via I2C to T6713 sensors and displays CO2 values
// We will be using the I2C hardware interface on the Arduino in
// combination with the built-in Wire library to interface.
// Arduino analog input 5 - I2C SCL
// Arduino analog input 4 - I2C SDA
/*
  In this example we will do a basic read of the CO2 value and checksum verification.
  For more advanced applications please see the I2C Comm guide.
*/
#include <Wire.h>  // Although Wire.h is part of the Ardunio GUI library, this statement is still necessary
#include "TelCO2sensor.h"
#define ADDR_6713  0x15 // default I2C slave address
TelClaireCO2 sensor(ADDR_6713);

// This is the default address of the CO2 sensor, 7bits shifted left.
void setup() { 
  int status = 0 ;
  Wire.begin ();
  Serial.begin(9600);
  Serial.println("Application Note AN161_ardunio_T6713_I2C");
 // sensor.calibration();  // single point calibration
 // Serial.print("calibrating ...");
  status = sensor.status(); // sensor status
  Serial.print("status:");Serial.println((unsigned int)status,DEC);
}

void loop() {

  int co2Value =sensor.readCO2();
  if (co2Value > 0)
  {
    Serial.print("CO2 Value: ");
    Serial.println(co2Value);
  }
  else
  {
    Serial.println("Checksum failed / Communication failure");
  }
  delay(2000);
}


