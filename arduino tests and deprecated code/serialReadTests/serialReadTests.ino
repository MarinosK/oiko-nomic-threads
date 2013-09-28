// int serialData = 0;
//int incomingByte = -1;
//int  val = 0; 
//char code[10]; 
//int bytesread = 0;

void setup()
{
  Serial.begin(9600);  
}

void loop() {
  readSerial();
}

void readSerial() {
  if (Serial.available() > 0) {
    // serialData = Serial.read();
    // Serial.println((int)serialData);
    Serial.println(Serial.read());
  }  else {
    // Serial.println("Serial not available..");
  }
    // Serial.write("abcdef");
}


//void readSerial() {
//  if(Serial.available() > 0) {          // if data available 
//    if((val = Serial.read()) == 10) {   // check for header start 
//      bytesread = 0; 
//      while(bytesread<1) {              // read 1 digit code 
//        if( Serial.available() > 0) { 
//          val = Serial.read(); 
//          if(val == 13) { // check for header end  
//            break;                       // stop reading 
//          } 
//          code[bytesread] = val;         // add the digit           
//          bytesread++;                   // ready to read next digit  
//        } 
//      } 
//      if(bytesread == 1) {              // if 1 digit read is complete 
//        incomingByte = int(code[0]);
//      } 
//      bytesread = 0; 
//      delay(50);                       // wait for a second 
//    } 
//  } 
//}
