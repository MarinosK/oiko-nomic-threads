
/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#include "segment.h"

// ============================= constructors ============================

Segment::Segment() : 
  mPattern(),
  mWidthIndex(0),
  mWidth(0),
  mRowIndex(0),
  mDoneFlag(false)
{ 
}

Segment::Segment(const cv::Mat &pattern, unsigned int widthIndex) :
  mPattern(pattern),
  mWidthIndex(widthIndex),
  mWidth(pattern.cols),
  mRowIndex(0),
  mDoneFlag(false)
{
}

Segment::Segment(const Segment& seg) :
  mPattern(seg.mPattern),
  mWidthIndex(seg.mWidthIndex),
  mWidth(seg.mWidth),
  mRowIndex(seg.mRowIndex),
  mDoneFlag(seg.mDoneFlag)
{  
} 

// ============================= operator= ============================

Segment Segment::operator=(const Segment& seg) {
  if (&seg != this) {
    mPattern = seg.mPattern;
    mWidthIndex = seg.mWidthIndex;
    mWidth = seg.mWidth;
    mRowIndex = seg.mRowIndex;
    mDoneFlag = seg.mDoneFlag;
  }
  return *this;
} 


// ============================= getWidth ============================
unsigned int Segment::getWidth() {
  return mWidth;
}

// ============================= getWidthIndex ============================
unsigned int Segment::getWidthIndex() {
  return mWidthIndex;
}

// ============================= getNextLine ============================
const cv::Mat Segment::getNextLineSegment() {

	// test pattern
  // cv::namedWindow( "Test");
//   cv::imshow( "Test", mPattern );
//   cv::waitKey(0);  

  if (mRowIndex < (mPattern.rows-1)) {
    return mPattern(cv::Rect(0,mRowIndex++,mWidth,1)); // notice mRowIndex is incremented 
  } else {
    mDoneFlag = true;
    return mPattern(cv::Rect(0,mRowIndex,mWidth,1));
  }
}

// ============================= done ============================
bool Segment::done() const {
  return mDoneFlag;
}


