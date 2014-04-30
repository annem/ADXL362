/*
 ADXL362_SimpleRead.ino -  Simple XYZ axis reading example
 for Analog Devices ADXL362 - Micropower 3-axis accelerometer
 go to http://www.analog.com/ADXL362 for datasheet
 
 License: GNU GPLv3 or later

 Copyright 2012 Anne Mahaffey
 
 Connect SCLK, MISO, MOSI, and CSB of ADXL362 to
 SCLK, MISO, MOSI, and DP 10 of Arduino 
 (check http://arduino.cc/en/Reference/SPI for details)
 
*/ 

#include <SPI.h>
#include <ADXL362.h>


ADXL362 xl;

int temp;
int XValue, YValue, ZValue, Temperature;


void setup(){
    Serial.begin(9600);
    xl.begin();                   // Setup SPI protocol, issue device soft reset
    xl.beginMeasure();            // Switch ADXL362 to measure mode  
    xl.checkAllControlRegs();     // Burst Read all Control Registers, to check for proper setup
	
    Serial.print("\n\nBegin Loop Function:\n");
}

void loop(){
    
    // read all three axis in burst to ensure all measurements correspond to same sample time
    xl.readXYZTData(XValue, YValue, ZValue, Temperature);  	 
    delay(100);                // Arbitrary delay to make serial monitor easier to observe
}

