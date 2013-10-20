/* controller.h */

/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

// sender sends messages to arduino

// listener listens for incoming messages

#ifndef _CONTROLLER_H
#define _CONTROLLER_H 1

#include <cstdio>
#include <string>
#include <cstddef>
#include <limits>
#include <iostream>

#include "opencv2/opencv.hpp"
#include "mar_utils.h"

#include "arduino-serial-lib.h"
#include "settings.h"

#include "sendOsc.h"

class Controller {
 private:
  static std::string arduinoID; // arduino path
  const int mBaudRate; // baudrate
  int mFd; // the serial file
  bool findPath();  // find arduino port's path and save it at arduinoID
 public:
  bool setUp();
  inline const std::string& getPath() const; // accessor
  bool sendMsg(const cv::Mat&); // send pattern to arduino
  bool waitForMsg(); // read message

  explicit Controller(); // Ctor
  explicit Controller(int); // Ctor with baudrate
  ~Controller(); // Dtor
  Controller(const Controller&) =delete; // no copy Ctor
  Controller& operator= (const Controller&) =delete; // no operator=
};

// inline member functions here
const std::string& Controller::getPath() const { 
  return arduinoID;
}

#endif /* _CONTROLLER_H */

