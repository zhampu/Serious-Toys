/*
  Arduino TFT text example

  This example demonstrates how to draw text on the
  TFT with an Arduino. The Arduino reads the value
  of an analog sensor attached to pin A0, and writes
  the value to the LCD screen, updating every
  quarter second.

  This example code is in the public domain

  Created 15 April 2013 by Scott Fitzgerald

  http://www.arduino.cc/en/Tutorial/TFTDisplayText

*/


float AccelMinX = 0;
float AccelMaxX = 0;
float AccelMinY = 0;
float AccelMaxY = 0;
float AccelMinZ = 0;
float AccelMaxZ = 0;
// char array to print to the screen
char sensorPrintout[16];

// ACCELEROMETER SENSOR INCLUDES
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);



#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pin definition for the Uno
#define cs   4
#define dc   5
#define rst  6

// pin definition for the Leonardo
// #define cs   7
// #define dc   0
// #define rst  1

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

void setup() {
  
  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  // set the font size
  TFTscreen.setTextSize(2);
  // write the text to the top left corner of the screen
  TFTscreen.text("wtf Sensor Value :\n ", 0, 0);
  // ste the font size very large for the loop
  TFTscreen.setTextSize(5);
  //#ifndef ESP8266
  //  while (!Serial); // for Leonardo/Micro/Zero
  //#endif
  //  Serial.begin(9600);
  //  Serial.println("ADXL345 Accelerometer Calibration");
  //  Serial.println("");

  /* Initialise the sensor */
    if (!accel.begin())
    {
      /* There was a problem detecting the ADXL345 ... check your connections */
      Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
      while (1);
    }

  accel.setRange(ADXL345_RANGE_16_G);
}

void loop() {

  // Read the value of the sensor on A0
  //String sensorVal = String(analogRead(A0));
  sensors_event_t event;
  accel.getEvent(&event);
  
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.stroke(255, 255, 255);
  //String sensorVal = String(analogRead(A0));
  String sensorVal = String((float)event.acceleration.y);
  Serial.print(event.acceleration.x);
  Serial.print("\t");
  Serial.print(event.acceleration.y);
  Serial.print("\t");
  Serial.println(event.acceleration.z);
  
  // convert theeading to a char array
  sensorVal.toCharArray(sensorPrintout, sizeof(sensorPrintout));
  TFTscreen.text(sensorPrintout, 0, 0);
  delay(200);


  // convert the reading to a char array
  //sensorVal.toCharArray(sensorPrintout, 4);
  // clear the screen with a black background
  //TFTscreen.background(0, 0, 0);
  // set the font color
  //TFTscreen.stroke(255, 255, 255);
  // print the sensor value
  //TFTscreen.text(sensorPrintout, 0, 10);
  // wait for a moment
  // erase the text you just wrote




}

