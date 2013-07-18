/*
  part of Oikonomic Threads project
  coded by Marinos Koutsomichalis (c) 2013, Heraklion
*/

// displays image output on the screen

#pragma once

#include <iostream>
#include <string>
#include <ctime>

#include <boost/lexical_cast.hpp>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "pattern.h"

class Visualizer {
 public:
  void setUp();
  void animate(Pattern &pattern);
  void still(Pattern &pattern, int lines);    	// display mats with highGUI
  void exportStill(Pattern &pattern, int lines );
  void test(cv::Mat);				// display matrix		
  void clean();
 private:
  cv::Mat mImage;
  std::string getCurrentDate();     // return current date (used to name Stills)
  unsigned int stillsIndex;	    // an index for the stills 
};
