/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#include "controller.h"

std::string Controller::arduinoID = "";

Controller::Controller() : 
  mBaudRate(115200),
  mFd(-1) {  
}

Controller::Controller(int baudrate_) : 
  mBaudRate(baudrate_),
  mFd(-1) {  
}

Controller::~Controller() {
  arduino_lib::serialport_close(mFd);
}

bool Controller::sendMsg(const cv::Mat& mat) {

  std::cout << "Attempting to send next line of pixels to knitting machine.." << std::endl;

  if (mFd == -1) {
      std::cout << "Serial communication has been interrupted or broken - pixels were not sent !" << std::endl;
      return false;
  } else {

    // convert mat to string
    std::string data;

    for (int i = (settings::width - 1); i >= 0; --i) {
      uchar bit = mat.at<uchar>(0, i);
      int castedBit = (int) bit; 
      if (castedBit == 0) { data.push_back('0'); } else { data.push_back('1'); }
    }

    int rc = arduino_lib::serialport_write(mFd, data.c_str()); // send pixels
    // DEBUG PRINT
    // DEBUG_PRINT(data);

    if (rc == -1) {
       std::cout << "Error sending the pixels to the machine !" << std::endl;
       return false;
    } else {
      return true;
    }
  }
}

bool Controller::waitForMsg() {
  std::cout << "Waiting for machine to knit line." << std::endl;
  if (mFd == -1) {
      std::cout << "Serial communication has been interrupted or broken - the machine never responded whether line was knitted or not.\nWill proceed nevertheless." << std::endl;
      return false;
  } else {
    int bufferSize = 7;
    char endOfLine = '\n';
    char buf[bufferSize]; // new character buffer
    memset(buf,0,bufferSize); // initiallize it

    // read characters over serial, wait until a newline or until 60 seconds have passed
    arduino_lib::serialport_read_until(mFd, buf, endOfLine, bufferSize, 1000000); // wait for app 16 minutes
    
    std::string test(buf); // convert char* to string 

    if (test == "done!\n") {
      std::cout << "Machine's response was positive: line has been knitted succesfully!" << std::endl;
      return true;
    } else {
      std::cout << "Knitting machine did respond, but the response was incomprehensible or the request timed out: it is not known whether line was knitted or not.\nWill proceed nevertheless." << std::endl;
      return true;
    }
  }
}

bool Controller::setUp() {
  bool foundPath = findPath(); // find path and save it at arduinoID
  std::cout << "Attempting to setup serial communication.." << std::endl;
  if (foundPath) {
    if( mFd != -1 ) {
      arduino_lib::serialport_close(mFd);
      std::cout << "Serial port was open, closing before attempting to setup communincation." << std::endl;
    } 

    // setup communication
    mFd = arduino_lib::serialport_init(arduinoID.c_str(), mBaudRate);
    
    if (mFd == -1) { 
      std::cout << "Failed to communicate over serial." << std::endl;
      return false;
    } else {
      std::cout << "Serial communication has been set." << std::endl;
      return true;
    }
    // flush serial port
    arduino_lib::serialport_flush(mFd);
  } else {
    std::cout << "Error: serial port not open !" << std::endl;
    return false;
  }
}

bool Controller::findPath() {

  std::cout << "Attempting to detect knitting machine over serial.." << std::endl;
  
  FILE *pipe = popen("ls /dev/tty.usbmodem*", "r");

  if (!pipe) {
    std::cout << "Failed to open temporary file; press Enter to try again" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    findPath();
  } else {

    char buffer[128];
    std::string result = "";

    while(!feof(pipe)) {
      if (fgets(buffer, 128, pipe) !=NULL) {
	result += buffer; 
      } 
    }

    if (result == "") {
      std::cout << "No knitting machine found ! Connect machine and press Enter to try again" << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
      findPath();
    } else {

      pclose(pipe);
      result = result.substr(0,result.length()-1); // remove gap from the end
      arduinoID = result;
      // post info to the console
      std::cout << "Knitting machine detected on serial port: " << arduinoID.c_str() << std::endl;
    
    }
  }
  return true;
}
