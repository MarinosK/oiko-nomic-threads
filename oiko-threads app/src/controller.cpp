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
#ifndef demo_mode
  arduino_lib::serialport_close(mFd);
#endif
}

bool Controller::sendMsg(const cv::Mat& mat) {

  std::cout << "Attempting to send next line of pixels to knitting machine.." << std::endl;

#ifdef dual_mode
  osc_communication::sendOsc("Attempting to send next line of pixels to knitting machine..");
#endif

#ifndef demo_mode
  if (mFd == -1) {
  std::cout << "Serial communication has been interrupted or broken - pixels were not sent !" << std::endl;
  osc_communication::sendOsc("Serial communication has been interrupted or broken - pixels were not sent !");
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
#ifdef dual_mode
  osc_communication::sendOsc("Error sending the pixels to the machine !");
#endif
  return false;
} else {
    return true;
  }
}
#endif 
}

bool Controller::waitForMsg() {
  std::cout << "Waiting for machine to knit line." << std::endl;
#ifdef dual_mode
  osc_communication::sendOsc("Waiting for machine to knit line.");
#endif
#ifndef demo_mode
  if (mFd == -1) {
  std::cout << "Serial communication has been interrupted or broken - the machine never responded whether line was knitted or not.\nWill proceed nevertheless." << std::endl;
  osc_communication::sendOsc("Serial communication has been interrupted or broken - the machine never responded whether line was knitted or not.\nWill proceed nevertheless.");
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
#ifdef dual_mode
  osc_communication::sendOsc("Machine's response was positive: line has been knitted succesfully!");
#endif
  return true;
} else {
    std::cout << "Knitting machine did respond, but the response was incomprehensible or the request timed out: it is not known whether line was knitted or not.\nWill proceed nevertheless." << std::endl;
#ifdef dual_mode
    osc_communication::sendOsc("Knitting machine did respond, but the response was incomprehensible or the request timed out: it is not known whether line was knitted or not.\nWill proceed nevertheless.");
#endif
    return true;
  }
  }
#endif
#ifdef demo_mode
    std::cout << "Machine's response was positive: line has been knitted succesfully!" << std::endl;
    osc_communication::sendOsc("Machine's response was positive: line has been knitted succesfully!");
    return true;
#endif
  }

    bool Controller::setUp() {
#ifndef demo_mode
    bool foundPath = findPath(); // find path and save it at arduinoID
    std::cout << "Attempting to setup serial communication.." << std::endl;
#ifdef dual_mode
    osc_communication::sendOsc("Attempting to setup serial communication..");
#endif
    if (foundPath) {
      if( mFd != -1 ) {
	arduino_lib::serialport_close(mFd);
	std::cout << "Serial port was open, closing before attempting to setup communincation." << std::endl;
#ifdef dual_mode
	osc_communication::sendOsc("Serial port was open, closing before attempting to setup communincation.");
#endif
      } 

	// setup communication
	mFd = arduino_lib::serialport_init(arduinoID.c_str(), mBaudRate);
    
	if (mFd == -1) { 
	std::cout << "Failed to communicate over serial." << std::endl;
#ifdef dual_mode
	osc_communication::sendOsc("Failed to communicate over serial.");
#endif
	return false;
      } else {
	  std::cout << "Serial communication has been set." << std::endl;
#ifdef dual_mode
	  osc_communication::sendOsc("Serial communication has been set.");
#endif
	  return true;
	}
	  // flush serial port
	  arduino_lib::serialport_flush(mFd);
	} else {
	  std::cout << "Error: serial port not open !" << std::endl;
#ifdef dual_mode
	  osc_communication::sendOsc("Error: serial port not open !");
#endif
	  return false;
	}
#endif 
#ifdef demo_mode
      std::cout << "Attempting to setup serial communication.." << std::endl;
      std::cout << "In demo no actual communication with the machine take place, therefore serial communication setup is being skipped." << std::endl;
      osc_communication::sendOsc("Attempting to setup serial communication..");
      osc_communication::sendOsc("In demo no actual communication with the machine take place, therefore serial communication setup is being skipped.");
      return true;
#endif
    }

      bool Controller::findPath() {

      std::cout << "Attempting to detect knitting machine over serial.." << std::endl;
#ifdef dual_mode
      osc_communication::sendOsc("Attempting to detect knitting machine over serial..");
#endif
#ifndef demo_mode
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
	  std::cout << "No knitting machine found ! Connect machine and press Enter to try again." << std::endl;
#ifdef dual_mode
      osc_communication::sendOsc("No knitting machine found ! Connect machine and press Enter to try again.");
#endif
	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	  findPath();
	} else {

	  pclose(pipe);
	  result = result.substr(0,result.length()-1); // remove gap from the end
	  arduinoID = result;
	  // post info to the console
	  std::cout << "Knitting machine detected on serial port: " << arduinoID.c_str() << std::endl;
#ifdef dual_mode
	std:string str = "Knitting machine detected on serial port: ";
	  osc_communication::sendOsc(str.append(arduinoID.c_str()));
#endif
    
	}
      }
#endif
#ifdef demo_mode
      std::cout << "Attempting to detect knitting machine over serial.." << std::endl;
      std::cout << "Knitting machine detected on serial port: " << "[ DEMO MODE ]" << std::endl;
#ifdef dual_mode
      osc_communication::sendOsc("Attempting to detect knitting machine over serial..");
      osc_communication::sendOsc("Knitting machine detected on serial port: [ DEMO MODE ]");

#endif
#endif
      return true;
    }
