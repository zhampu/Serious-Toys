// Make the buffer bigger
char sensorPrintout[16];

// ACCELEROMETER SENSOR INCLUDES
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// TFT Screen
#include <TFT.h>
#include <SPI.h>

// pin definition for the Micro
#define cs   4
#define dc   5
#define rst  6


TFT TFTscreen = TFT(cs, dc, rst);
int width;
int height;


// variables of the ball

float ballDirectionX = 0;
float ballDirectionY = 0;


float ballX, ballY, oldBallX, oldBallY;

float bounceCoef = 0.6;

int refreshPeriod = 50; // ms
unsigned long nextUpdate = 0;

int ballRadius = 20;

void setup() {
  // initialize the display
  TFTscreen.begin();
  // black background
  TFTscreen.background(0, 0, 0);

    // save the width and height of the screen
  width = TFTscreen.width();
  height = TFTscreen.height();

  /* Initialise the sensor */
  if (!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while (1);
  }

  accel.setRange(ADXL345_RANGE_16_G);

  ballX = oldBallX = width / 2;
  ballY = oldBallY = height / 2;

  TFTscreen.noFill();
}

void loop() {

  // set the fill color to black and erase the previous
  // position of the paddle if different from present
  TFTscreen.fill(0, 0, 0);

  // update the ball's position and draw it on screen
  if (millis() > nextUpdate) {
    nextUpdate += refreshPeriod;
    moveBall();
  }
}

// this function determines the ball's position on screen
void moveBall() {

  sensors_event_t event;
  accel.getEvent(&event);

  // Updte direction from accelerometer position
  ballDirectionX += event.acceleration.x / 10;
  ballDirectionY += event.acceleration.y / 10;

  // update the ball's position
  ballX += ballDirectionX;
  ballY -= ballDirectionY;

  // if the ball goes offscreen, reverse the direction:
  if (ballX > width || ballX < 0) {
    ballDirectionX = bounceCoef * -ballDirectionX;
    ballX = constrain(ballX, 0, width);
  }

  if (ballY > height || ballY < 0) {
    ballDirectionY = bounceCoef * -ballDirectionY;
    ballY = constrain(ballY, 0, height);
  }


  // erase the ball's previous position
  if ((int)oldBallX != (int)ballX || (int)oldBallY != (int)ballY) {
    TFTscreen.stroke(0, 0, 0);
    TFTscreen.circle(oldBallX, oldBallY, ballRadius);
  }


  // draw the ball's current position
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.circle(ballX, ballY, ballRadius);

  oldBallX = ballX;
  oldBallY = ballY;

  //  TFTscreen.background(0, 0, 0);

  Serial.print(event.acceleration.x);
  Serial.print("\t");
  Serial.print(event.acceleration.y);
  Serial.print("\t");
  Serial.print(ballX);
  Serial.print("\t");
  Serial.print(ballY);
  Serial.println();

}




