/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <libproc.h>

#include "mar_utils.h"

#include "boost/lexical_cast.hpp"
#include "opencv2/opencv.hpp"

#include "settings.h"
#include "data.h"
#include "segment.h"

#include "mar_utils.h"

class Pattern {
 private:
  cv::Mat mOutput;	 // the output line (nextLine() returns this)
  std::vector<cv::Mat> mOriginals;  // vector with the original patterns
  std::vector<std::vector<Segment> > mPatterns;
  std::vector<std::string> mPaths; // the paths of the image files
  Data mData;		      // the data retrieving object
  Entry mEntry;		     // next entry used internally by nextEntry()
  bool mEntryFlag;	     // flag used internally by nextEntry()
  // std::vector<Segment>::iterator patternIterator; // the position of the next iterator to start looking for finished patterns

  int nextEntry();    // return next entry (be it date or amount)
  bool testIfDone(const Segment&);

  void encode(int); // encode entries to an array of normalized patterns

  std::vector<unsigned int> distribute(int parts); // calculates the distribution of the numbers -> check README.md
  int random(int,int);	  // random numbers in a min/max range
 
 public:
 void savePosition();
  void setUp();
  cv::Mat nextLine();	   // retrieves data, encodes them and outputes next line for displaying/knitting
  explicit Pattern(); // explicit ctor
  Pattern(const Pattern&) =delete; 
  Pattern& operator=(const Pattern&) =delete;
  ~Pattern() =default;
};
