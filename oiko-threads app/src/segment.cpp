
#include "segment.h"

// ======================== c/d-tors/operator=/ ========================
Segment::Segment() : 
  mPattern {},
  mPositionIndex {0},
  mWidth {0},
  mRowIndex {0},
  mDoneFlag {false} { }

Segment::Segment(const cv::Mat& pattern, unsigned positionIndex) :
  mPattern {pattern},
  mPositionIndex {positionIndex},
  mWidth {static_cast<unsigned>(pattern.cols)},
  mRowIndex {0},
  mDoneFlag {false} {}

Segment::Segment(const Segment& seg) :
  mPattern {seg.mPattern},
  mPositionIndex {seg.mPositionIndex},
  mWidth {seg.mWidth},
  mRowIndex {seg.mRowIndex},
  mDoneFlag {seg.mDoneFlag} {}

Segment::Segment(Segment&& seg) :
  mPattern {std::move(seg.mPattern)},
  mPositionIndex {std::move(seg.mPositionIndex)},
  mWidth {std::move(seg.mWidth)},
  mRowIndex {std::move(seg.mRowIndex)},
  mDoneFlag {std::move(seg.mDoneFlag)} { }

Segment Segment::operator=(const Segment& seg) {
  if (&seg != this) {
    mPattern = seg.mPattern;
    mPositionIndex = seg.mPositionIndex;
    mWidth = seg.mWidth;
    mRowIndex = seg.mRowIndex;
    mDoneFlag = seg.mDoneFlag;
  }
  return *this;
}

Segment Segment::operator=(Segment&& seg) {
  assert(this != &seg);
  mPattern = std::move(seg.mPattern);
  mPositionIndex = std::move(seg.mPositionIndex);
  mWidth = std::move(seg.mWidth);
  mRowIndex = std::move(seg.mRowIndex);
  mDoneFlag = std::move(seg.mDoneFlag);
  return *this;
} 

// ============================= getNextLine ============================
const cv::Mat Segment::getNextLineSegment() {
  if (mRowIndex != (mPattern.rows - 1))
    return mPattern(cv::Rect(0,mRowIndex++,mWidth,1));
  else { // when done just keep returning the last line
    mDoneFlag = true;
    return mPattern(cv::Rect(0,mRowIndex,mWidth,1));
  }
}
