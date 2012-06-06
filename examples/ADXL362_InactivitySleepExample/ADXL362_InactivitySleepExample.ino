
/*
InactivitySleepExample.ino for 
Analog Devices ADXL362 - Micropower 3-axis accelerometer
go to https://www.analog.com/adxl362 for datasheet

Arduino will "go to sleep" when circuit has been motionless for
a short period of time.  Arduino will "wake-up" when moved.


License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
to use and abuse this code however you'd like. If you find it useful
please attribute, and SHARE-ALIKE!

Created June 2012
by Anne Mahaffey - hosted on https://github.com/annem/ADXL362

Connect SCLK, MISO, MOSI, and CSB of ADXL362 to
SCLK, MISO, MOSI, and DP 10 of Arduino 
( See http://arduino.cc/en/Reference/SPI for details)

Connect INT1 of ADXL362 to DP2 of Arduino
( See http://arduino.cc/en/Reference/AttachInterrupt for details)

*/ 



// Download LowPower library from https://github.com/rocketscream/Low-Power
#include <LowPower.h>

#include <SPI.h>
#include <ADXL362.h>

ADXL362 xl;

//  Setup interrupt on Arduino
//  See interrupt example at http://arduino.cc/en/Reference/AttachInterrupt
//
int interruptPin = 2;          //Setup ADXL362 interrupt output to Interrupt 0 (digital pin 2)
int interruptStatus = 0;



void setup(){

    // Startup, soft reset
    Serial.begin(9600);
    xl.begin();                //soft reset
    delay(1000);    
    
	
    // Setup digital pin 7 for LED observation of awake/asleep  
    pinMode(7, OUTPUT);    
    digitalWrite(7, HIGH);
    

    //  Setup Activity and Inactivity thresholds
    xl.setupDCActivityInterrupt(300, 10);
    xl.setupDCInactivityInterrupt(80, 30);
	Serial.println();

	
    // Setup ADXL362 for proper autosleep mode
    //  STILL NEEDS CLEANUP OF COMMENTING
    xl.SPIwriteOneRegister(0x27, 0x3F); // AC both, link, loop, inact, act,     
    xl.SPIwriteOneRegister(0x2A, 0x40); // int 1 = Awake   
    xl.SPIwriteOneRegister(0x2D, 0x04); // autosleep
    
	
    // turn on Measure mode
    xl.beginMeasure();                      // DO LAST! enable measurement mode   
    xl.checkAllControlRegs();               // check some setup conditions    
    delay(100);
    
	
    // Setup interrupt function on Arduino
    // IMPORTANT - Do this last in the setup, after you have fully configured ADXL.  You don't want the Arduino to go to sleep before you're done with setup
    pinMode(2, INPUT);    
    attachInterrupt(0, interruptFunction, RISING);  // A high on output of ADXL interrupt means ADXL is awake, and wake up Arduino 
}



void loop(){
  //
  //  Check ADXL362 interrupt status to determine if it's asleep
  //
  interruptStatus = digitalRead(interruptPin);
  
  if(interruptStatus == 0) { 
    Serial.print("\nADXL went to sleep - Put Arduino to sleep now \n");
    digitalWrite(7, LOW);    // Turn off LED as visual indicator of asleep
    delay(1000);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);     
  }
  else{
    delay(10);
    digitalWrite(7, HIGH);    // Turn on LED as visual indicator of awake
    xl.readXData();
    xl.readYData();
    xl.readZData();
    Serial.println();     
  }
  // give circuit time to settle after wakeup
  delay(20);
}

//
// Function called if Arduino detects interrupt activity
//
void interruptFunction(){
  Serial.println("\nArduino is Awake! \n");
}