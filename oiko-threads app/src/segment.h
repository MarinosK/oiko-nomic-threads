/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/
// Segment is a 'smart' cv::Mat which also holds info of its target coordinates (where exactly it should be knitted)

#ifndef SEGMENT_H
#define SEGMENT_H

#include <opencv2/opencv.hpp>

/// structure holding a scaled mottif (a cv::Mat) alongs its position index and width info
struct Segment {
 private:
  cv::Mat mPattern;
  unsigned mPositionIndex;
  unsigned mWidth;
  unsigned mRowIndex;
  bool mDoneFlag;
 public:
  /// get segment's width
  inline unsigned getWidth() const { return mWidth; }
  /// get segment's position index 
  inline unsigned getPositionIndex() const { return mPositionIndex; }
  /// false when there are no more lines to pop
  inline bool done() const { return mDoneFlag; }
  /// return the entire wrapped cv::Mat 
  const cv::Mat& getMat() const { return mPattern; }
  /// pop the next line (an 1-dimensional cv::Mat)
  const cv::Mat getNextLineSegment();
  /// constructor
  explicit Segment();
  /// constructor
  Segment(const cv::Mat&, unsigned positionIndex);
  /// copy constructor
  Segment(const Segment&);
  /// move constructor 
  Segment(Segment&&);
  /// assignement operator
  Segment operator=(const Segment&);
  /// move assignment operator
  Segment operator=(Segment&&);
  /// default destructor
  ~Segment() =default;
};

#endif
