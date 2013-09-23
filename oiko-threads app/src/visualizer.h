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

#include "mar_utils.h"

class Visualizer {
private:
  const int mWidth, mHeight;       // width and height..
  const  int mLineHeight;   // factor to calculate resizing (for animation)
  int mStillsIndex;	    // an index for the stills 
  cv::Mat mImage;		    // matrix to update for animation
  std::string getCurrentDate();     // return current date (used to name Stills)
 public:
  explicit Visualizer(); // ctor
  explicit Visualizer(const unsigned int width, const unsigned int height); // ctor
  ~Visualizer();  // dtor
  Visualizer(const Visualizer&) =delete;
  Visualizer& operator=(const Visualizer&) =delete; 

  void animate(cv::Mat mat);
  void still(Pattern &pattern, int lines);    	// display mats with highGUI
  void exportStill(Pattern &pattern, int lines );
  void test(cv::Mat);				// display matrix	   
};
