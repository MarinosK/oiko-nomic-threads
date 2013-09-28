// Oiko-nomic Threads 
/*
OIKO-NOMIC THREADS An installation for algorithmically controlled 
knitting machine and open data (c) 2013 Marinos Koutsomichalis, 
Maria Varela, Afroditi Psarra

Software and Hardware development for Oiko-nomic threads was 
realized by Marinos Koutsomichalis, Afroditi Psarra and Maria Varela. Related code, texts and images are distributed under the Attribution-NonCommercial-ShareAlike 3.0 Unported Creative Commons Licence (details here: http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US).

THIS MATERIAL IS DISTRIBUTED AS IS WITH NO GUARANTEE OF 
FUNCTIONALITY OR RELEVANCE TO THIRD PARTY PROJECTS - 
THE DEVELOPERS ARE THUS NOT TO BE HELD RESPONSIBLE FOR PERSONAL 
INJURIES, HARDWARE, FINANCIAL, OR ANY OTHER LOSSES AND IN GENERAL 
FOR ANY MISFORTUNATE EVENT CAUSED BY THE DESCRIBED SOFTWARE/HARDWARE
OR IN THE PROCESS OF ATTEMPTING TO IMPLEMENT IT. IF YOU DON'T AGREE 
WITH THE AFOREMENTIONED YOUR ARE NOT ALLOWED TO USE THE MATERIAL 
PROVIDED HEREIN

Contact: 
marinos [at] agxivatein.com 
stereochic [at] gmail.com 
m.mivon [at] gmail.com

*/

#include "solenoids.h" // the solenoids port mappings

// -------------------------------- constants ---------------------- 
#define gEncoderA 2 // IR sensor connected to to digital pin2
//#define gEncoderB 3
//#define gEncoderC 4 // 8 segment encoder
#define gLeftSensor 3
#define gRightSensor 5


// -------------------------------- global variables ---------------------- 

volatile int gEncoderPosition = 0; // encoder's position

// used to calculate direction and end of line
short gDirection = 0;      // 0 is for UNDEFINED direction, -1 is for Left-Right, +1 is for Right-Left
short gPrevDirection = 0;  // the previous direction
byte gEndOfLine = 0; // end of Line
byte gPrevEndOfLine = 0; // Previous end of Line
byte gLeft = 0;   // flag to indicate if left sensor has been hit once
byte gRight = 0;  // flag to indicate if right sensor has been hit once
byte gLeftSensorValue = LOW;        // left sensor value
byte gLeftSensorPrevValue  = LOW;   // left sensor previous value
byte gRightSensorValue = LOW;       // right sensor value
byte gRightSensorPrevValue  = LOW;  // right sensor previous value

// used to calculate the stitch position
int gStitch = 0;
int gPrevStitch = 0;

short gSolenoids[] = { // solenoids array
  // SOL_1, SOL_2, SOL_3, SOL_4, SOL_5, SOL_6, SOL_7, SOL_8, SOL_9, SOL_10, SOL_11, SOL_12, SOL_13, SOL_14, SOL_15, SOL_16
  // solenoids are mirrored !!!
  SOL_1, SOL_2, SOL_3, SOL_4, SOL_5, SOL_6, SOL_7, SOL_8, SOL_16, SOL_15, SOL_14, SOL_13, SOL_12, SOL_11, SOL_10, SOL_9
};

// used to update pixels Array and respond to oiko-threads-app
int gPixelsIndex = 16; // gPixels array index 
boolean gPendingRequest = false;

byte gPixels[256] = { 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // these have to be always 1
  // useful pixels section starts here
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  // useful pixels section ends here  
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, // array ends here
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// -------------------------------- interrupt ----------------------------

void gEncoderInterrupt() { 
  gEncoderPosition++;
}

// -------------------------------- set up -------------------------------

void setup() {
  Serial.begin(115200); // begin serial
  
  pinMode(gEncoderA, INPUT); // encoder is input
  pinMode(gLeftSensor, INPUT); // encoder is input
  pinMode(gRightSensor, INPUT); // encoder is input
  
  attachInterrupt(gEncoderA, gEncoderInterrupt, RISING); //interrupt 0 on UNO, 2 on DUE

  for(int i =0;i<16;i++){ // set solenoids pins to output 
    pinMode(gSolenoids[i], OUTPUT);
  }
  
  for(int i =0;i<16;i++){ // set solenoids to 0
    digitalWrite(gSolenoids[i],0);
  }
  
  gCalculateDirectionAndEndOfLine(); // calculate direction
}

// -------------------------------- loop ---------------------------------

void loop() {
  
  gPrevEndOfLine = gEndOfLine; // set previous end of line
  gUpdatePixelsSerial(); // update pixels according to serial input  
  
  if (gPixelsIndex > 170) gPendingRequest = true;
  
  gCalculateDirectionAndEndOfLine(); // calculate the direction of the carriage
  gResetEncoderPosition();    // reset gEncoderPosition on the endOfLines
  gCalculateStitch(); // calculate stitch

  if (gPendingRequest) gSetSolenoids(); // set solenoids accordingly;
 
  if (gPendingRequest && (gEndOfLine == 1) && (gPrevEndOfLine == 0)) {
    gPendingRequest = false; // send gPendingRequest to false
    gPixelsIndex = 16;
    Serial.print("done!\n"); // send done to oiko-threads-app  
  }
  
    // debug print
//  Serial.print(gEncoderPosition);
//  Serial.print("  ");
//  Serial.println(gStitch);
}

// ------------- Calculate Direction and End Of Line  ---------------------------------

void gCalculateDirectionAndEndOfLine() {
  
  gPrevDirection = gDirection; // update previous direction
  
  // update previous values
  gLeftSensorPrevValue = gLeftSensorValue;
  gRightSensorPrevValue = gRightSensorValue;
  // read current values
  gLeftSensorValue = digitalRead(gLeftSensor); 
  gRightSensorValue = digitalRead(gRightSensor);

  // increment gLeft/gRight if carriage movement is detected
  if ((gLeft == 0) && (gLeftSensorValue == LOW)) {
    gLeft = 1;
  } 
  if ((gRight == 0) && (gRightSensorValue == LOW)) {
    gRight = 1;
  }

  // reset gLeft/gRight if previously we had an end of line and a change in the detected value
  if ((gLeft == 1) && (gRightSensorPrevValue == HIGH) && (gRightSensorValue == LOW) && (gEndOfLine == 1)) {
    gLeft = 0;
  }
  if ((gRight == 1) && (gLeftSensorPrevValue == HIGH) && (gLeftSensorValue == LOW) && (gEndOfLine == 1)) {
    gRight = 0;
  }
  
  // set direction/end of line accordingly
  if ((gLeft == 0) && ( gRight == 1)) {
    gDirection = 1;
    gEndOfLine = 0;
  } else if ((gLeft == 1) && ( gRight == 0)) {
    gDirection = -1;
    gEndOfLine = 0;
  } else if (((gLeft == 0) && ( gRight == 0)) || ((gLeft == 1) && (gRight == 1 ))) {
    gDirection = 0; 
    gEndOfLine = 1;
  }
  
  // debug print
//  Serial.print(gDirection);
//  Serial.print("  ");
//  Serial.print(gEndOfLine);
//  Serial.print("  ");
//  Serial.print(gLeft);
//  Serial.print("  ");
//  Serial.print(gRight);
//  Serial.print("  ");
//  Serial.print(gLeftSensorValue);
//  Serial.print("  ");
//  Serial.println(gRightSensorValue);
}

// ------------- reset encoder position  ---------------------------------
void gResetEncoderPosition() {
  if (gEndOfLine == 1) {
    gEncoderPosition = 0;
  } 
}

// ------------- Calculate Stitch  ---------------------------------

void gCalculateStitch() { 
  gPrevStitch = gStitch; // update previous stitch
  
  /* gEncoderPosition increments from 0 to 256, encoderPosition  will go from 0 to 256 and then backwards */
  int encoderPosition = 0; // this is not the same as gEncoderPosition !! 
  
  if (gDirection == -1) {  // ****** I might need to reverse these rules !!!
    encoderPosition = gEncoderPosition;
  } else if (gDirection == 1) {
    encoderPosition = 256 - gEncoderPosition;
    // encoderPosition = gEncoderPosition;
  } else {
    encoderPosition = 0;
  }
  
  gStitch = encoderPosition - 28;
}

// --------------------- Set Solenoids  ---------------------------------
void gSetSolenoids () {  
  
    if( gPrevStitch != gStitch) { // if stitch has moved
      // gPrevStitch = gStitch
      
      int stitchPosition = gStitch + 28;
      int index = abs(stitchPosition) % 16;
      
      if(gDirection == -1){  // RIGHT direction 
        int pixelsIndex = stitchPosition - 8; // -16
        if((pixelsIndex>=0) && (pixelsIndex<254)){
          int pixelValue = gPixels[pixelsIndex]; 
          digitalWrite(gSolenoids[index],pixelValue);
//          // debug print
//          Serial.print(index);
//          Serial.print("  ");
//          Serial.print(pixelsIndex);
//          Serial.print("  ");
//          Serial.println(pixelValue);
        }
      } else if (gDirection == 1) {  // LEFT direction 
        int pixelsIndex = stitchPosition - 40; // -48
        if((pixelsIndex>=0) && (pixelsIndex<254)){
          int pixelValue = gPixels[pixelsIndex]; 
          digitalWrite(gSolenoids[index],pixelValue);
//          // debug print
//          Serial.print(index);
//          Serial.print("  ");
//          Serial.print(pixelsIndex);
//          Serial.print("  ");
//          Serial.println(pixelValue);
        } 
      } else {
          digitalWrite(gSolenoids[index], LOW);// zero out all solenoids
      }
    } 
}

// ------------- update Pixels Serial  ---------------------------------

void gUpdatePixelsSerial() {
  if (Serial.available() > 0) {

    // update pending request
    // gPendingRequest = true;
    
    // read input
    int value = Serial.read(); 
    
    // set pixel value
    byte pixel = 0; 
    if (value == 48) {
      pixel = 0;
    } else {
      pixel = 1;
    }
    
    // update gPixels
    gPixels[gPixelsIndex] = pixel;
    
    // update index 
    if (gPixelsIndex <= 175) ++gPixelsIndex;  
    // if (gPixelsIndex > 175) gPixelsIndex = 16;
  }
}
