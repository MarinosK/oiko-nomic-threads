int gPixelsIndex = 16;
boolean gMessageReceived = false;

byte gPixels[256] = { 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // these have to be always 1   
  // useful pixels section starts here
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  // useful pixels section ends here  
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, // array ends here
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("starting..");
}

void loop() {
  // put your main code here, to run repeatedly: 
  updatePixelsSerial();
  
  if (gPixelsIndex == 175) {
    for (int i=0; i<256; ++i) {
      Serial.print(gPixels[i]);
    }
    Serial.println("");
  }
  
  if (gMessageReceived) {
    delay(1000);
    Serial.print("done!\n");
    gMessageReceived = false;
  }
 
  // Serial.write("done!\n");
  // Serial.println("done!");
  // delay(100);
}

void updatePixelsSerial() {
  if (Serial.available() > 0) {

    // read input
    int value = Serial.read(); 
    gMessageReceived = true;
    
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
    if (gPixelsIndex > 175) {
      gPixelsIndex = 16;
    } else {
      ++gPixelsIndex;
    } 
  }
};

// remember to reset gPixelsIndex on EndOfLines
