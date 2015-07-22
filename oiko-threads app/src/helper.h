/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

// settigns, constants and helper functions

#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <exception> 
#include <chrono>
#include <random>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <cstdio>
#include <limits>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "constants.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

// #include <cstddef>

#ifndef EMULATION_MODE
#include "arduino-serial-lib.h"
#endif

/// useful variables and constants 
namespace settings {

  /// visuals window's width (setable via the exe's first argument) 
  extern unsigned width;
  /// visuals window's height (setable via the exe's first argument) 
  extern unsigned height;
  /// maximum wait-time for the machine to respond in seconds; in emulation mode this corresponds to  the scrolling speed) 
  extern unsigned speed;
  /// hardware path (tracked at runtime)
  extern const std::string hardwarePath;
  /// width in stitches
  constexpr unsigned knitWidth {KNIT_WIDTH};
  /// name of the GUI Window
  constexpr char const* guiWindow{GUI_WINDOW_NAME};
  /// default baud rate
  constexpr unsigned baudRate {BAUD_RATE};
  /// default OSC IP Address
  constexpr char const* oscPath {OSC_PATH};
  /// default OSC Port
  constexpr int oscPort {OSC_PORT};
  /// the preample to print in the console
  constexpr char const* preample = PREAMPLE;

  /// the path of the data-file
  extern const std::string dataFile;
  /// the paths to the digital mottifs (screen analysis) 
  extern const std::vector<const std::string> pathsToMottifsForShowing;
  /// the paths to the digital mottifs (stitch analysis) 
  extern const std::vector<const std::string> pathsToMottifsForKniting;
}

/// various helper functions
namespace helper {
  /// used internally by main to set width and height
  void setWidthAndHeightAndSpeed (int, char**);
  /// print to stdout (and send an OSC if compiled in DUAL_MODE)
  template <typename T> void log(T rhs) { 
    std::cout << rhs << std::endl;
#ifdef DUAL_MODE
    sendOsc(rhs);
#endif
  }
#ifndef EMULATION_MODE
  /// find hardware and update internal paths
  std::string trackHardware ();
#endif
  /// throw exception (and send an OSC if compiled in DUAL_MODE)
  template <typename E> // E should be an exception
  void myThrow(const std::string& message) {
#ifdef DUAL_MODE
    helper::sendOsc(message);
#endif
    throw E(message);
  }
  /// send messages over osc
  void sendOsc(const std::string&);
  /// quickly visualise a cv::Mat (for testing)
  void testShow(cv::Mat);
}

#endif
