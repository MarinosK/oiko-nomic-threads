
/*
  part of Oikonomic Threads project
  coded by Marinos Koutsomichalis (c) 2013, Heraklion
*/

// setUp loads patterns into memory

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "boost/lexical_cast.hpp"
#include "opencv2/opencv.hpp"

#include "settings.h"
#include "data.h"

class Pattern {
 public:
  explicit Pattern();
  void setUp();
  cv::Mat nextLine();		   // retrieves data, encodes them and outputes next line for displaying/knitting
 private:
  Pattern(const Pattern &pattern); // private copy ctor to disable copying
  Pattern& operator=(const Pattern &pattern); // private assignment operator
  cv::Mat mOutput;		   // the output line (nextLine() returns this)
  unsigned int mRowIndex;	   // counts the rows so as to re-encode patterns once the end of some item is reached
  unsigned int mMaxHeight;	   // the maximum height a pattern has - used to calculate the height of the destination pattern
  unsigned int mChangeIndex;	   // the height of the smallest item in a pattern - when mRowIndex = mChangeIndex a new series of Patterns will be created and merged with the old ones
  std::vector<cv::Mat> mOriginals;  // vector with the original patterns
  std::vector<cv::Mat> mPatterns;   // normallized and processed patterns to use
  std::vector<std::string> mPaths;  // the paths of the image files
  Data mData;			   // the data retrieving object
  bool mEntryFlag;		   // flag used internally by nextEntry()
  Entry mEntry;			   // next entry used internally by nextEntry()
  
  // helper functions
  int nextEntry();		    // return next entry (be it date or amount)
  std::vector<cv::Mat> encode(int); // encode entries to an array of normalized patterns
  std::vector<unsigned int> distribute(int parts); // calculates the distribution of the numbers -> check README.md
  int random(int,int);		   // random numbers in a min/max range
};
