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