/*
 Arduino Library for Analog Devices ADXL362 - Micropower 3-axis accelerometer
 go to https://www.analog.com/adxl362 for datasheet
 
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created June 2012
 by Anne Mahaffey - hosted on https://github.com/annem/ADXL362
 
 */ 

#include "Arduino.h"

#ifndef ADXL362_h
#define ADXL362_h


class ADXL362
{
public:

	ADXL362();
	
	//
	// Basic Device control and readback functions
	//
	void begin(); 		
	void beginMeasure(); 
	int readXData();
	int readYData();
	int readZData();
	int readTemp();
	
	//
	// Activity/Inactivity interrupt functions
	//
	void setupDCActivityInterrupt(int threshold, byte time);	
	void setupDCInactivityInterrupt(int threshold, int time);
    void setupACActivityInterrupt(int threshold, byte time);
	void setupACInactivityInterrupt(int threshold, int time);
	
	
	void checkAllControlRegs();
	
	
	//  Low-level SPI control, to simplify overall coding
	byte SPIreadOneRegister(byte regAddress);
	void SPIwriteOneRegister(byte regAddress, byte regValue);
	int  SPIreadTwoRegisters(byte regAddress);
	void SPIwriteTwoRegisters(byte regAddress, int twoRegValue);

	
private:

};

#endif