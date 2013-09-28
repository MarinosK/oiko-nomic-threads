// 1 or HIGH knit background colour - needle position B
// 0 or LOW knit pattern colour - needle position D


#include "definitions.h"

int encoder = 2; // IR sensor connected to to digital pin2
volatile int pos = 0;
int stitch =0;
int lastStitch = 0;
int currentStitchSetup = 0;
int currentSolenoidIDSetup = 0;
int currentPixState = 0;
int group= 0;
// solenoids array
int solenoids[] = {
  SOL_1, SOL_2, SOL_3, SOL_4, 
  SOL_5, SOL_6, SOL_7, SOL_8,
  SOL_9, SOL_10, SOL_11, SOL_12,
  SOL_13, SOL_14, SOL_15, SOL_16
};

// needles array
int pixels[256] = { 
  1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 9
  1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, // 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void setup() {

  Serial.begin(115200);
  pinMode(encoder, INPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(encoder, count, RISING); //interrupt 0 on UNO, 2 on DUE
  Serial.println("starting...");     
  digitalWrite(13,LOW);

  for(int i =0;i<16;i++){
    pinMode(solenoids[i], OUTPUT);
  }
  
  pos = 0; // make sure pos is 0
}


void loop() {

//    if( encoder4Pos !=0 ){ 
//      encoder1Pos = encoder4Pos/4;
//      stitch = (encoder1Pos)-28; 
//    }
//    else{
//      encoder1Pos = 0;
//      stitch = -28;
//    }

//  if( lastStitch!=stitch){
//    lastStitch = stitch;

   if (pos > 15) {
     int i = abs(pos-8) % 16;
     currentStitchSetup = pos - 16;
     currentSolenoidIDSetup = i;
     if(currentStitchSetup>=0 && currentStitchSetup<254){
       currentPixState = pixels[currentStitchSetup];
       // if(solenoids[i] != currentPixState) {
         digitalWrite(solenoids[i], currentPixState);
       }
     }
   // }
}

void count() { 
  pos++;
}





