/*
 Arduino Library for Analog Devices ADXL362 - Micropower 3-axis accelerometer
 go to http://www.analog.com/ADXL362 for datasheet
 
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created June 2012
 by Anne Mahaffey - hosted on http://annem.github.com/ADXL362
 
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
	void readXYZTData(int XData, int YData, int ZData, int Temperature);
	int readTemp();
	
	//
	// Activity/Inactivity interrupt functions
	//
	void setupDCActivityInterrupt(int threshold, byte time);	
	void setupDCInactivityInterrupt(int threshold, int time);
    void setupACActivityInterrupt(int threshold, byte time);
	void setupACInactivityInterrupt(int threshold, int time);
	
	// need to add the following functions
	// void mapINT1(
	// void mapINT2
	// void autoSleep
	// void activityInterruptControl
	//		-Activity, Inactivity, Both
	//		- Referenced, Absolute
	//		- Free Fall, Linked Mode, Loop Mode
	
	
	void checkAllControlRegs();
	
	
	//  Low-level SPI control, to simplify overall coding
	byte SPIreadOneRegister(byte regAddress);
	void SPIwriteOneRegister(byte regAddress, byte regValue);
	int  SPIreadTwoRegisters(byte regAddress);
	void SPIwriteTwoRegisters(byte regAddress, int twoRegValue);

	
private:

};

#endif