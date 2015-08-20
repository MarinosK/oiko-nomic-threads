/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#ifndef _CONTROLLER_H
#define _CONTROLLER_H 1

#include <sstream>
#include <opencv2/opencv.hpp>
#include "arduino-serial-lib.h"
#include "helper.h"

#ifdef DEBUG
#include "mar_utils.h"
#endif 

/// overloaded operator<< (reads pixels from a cv::mat to an ostream)
std::ostringstream& operator<< (std::ostringstream&, const cv::Mat&);

/// Controller is responsible for all IO communication with the knitting machine 
class Controller {
 private:
  static const std::string arduinoID; 
  static constexpr int mBaudRate {settings::baudRate};
  int mFd; // the serial file
 public:
  /// send a knitting pattern to the machine
  bool sendMsg(const cv::Mat&);
  /// wait for the machine to respond
  bool waitForMsg(); // read message
  /// constructor
  Controller(); // Ctor
  /// destructor
  ~Controller(); // Dtor
  Controller(const Controller&) =delete; 
  Controller(Controller&&) =delete; 
  Controller& operator= (const Controller&) =delete; 
  Controller& operator= (Controller&&) =delete; 
};

#endif /* _CONTROLLER_H */

