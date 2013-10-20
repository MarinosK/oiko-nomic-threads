/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

// Segment is a 'smart' cv::Mat which also holds info of its target coordinates (where exactly it has to be knitted)

#pragma once

#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "mar_utils.h"


// image segment (also holding width and rowIndex for each mat)
class Segment {
 private:
  cv::Mat mPattern;
  unsigned int mWidthIndex;
  unsigned int mWidth;
  unsigned int mRowIndex;
  bool mDoneFlag;
 public:
  unsigned int getWidth();
  unsigned int getWidthIndex();
  const cv::Mat getNextLineSegment();
  bool done() const;
  explicit Segment(); // Ctor
  explicit Segment(const cv::Mat&, unsigned int); // Ctor
  Segment(const Segment&); // copy Ctor
  Segment operator=(const Segment&);
  ~Segment() =default;
};


