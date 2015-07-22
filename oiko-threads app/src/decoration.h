/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#ifndef DECORATION_H
#define DECORATION_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <mar_utils.h>
#include <boost/lexical_cast.hpp>
#include "helper.h"
#include "data.h"
#include "segment.h"

using Pattern = std::vector<Segment>; 

/// structure holding the decoration to knit; it retrieves entries from a Data object, encodes them accordingly into a vector of Segments and makes sure the more mottifs are added when the shortest in the vector is done; (see the visualization algorithm description for more info)
class Decoration {
 private:
  const std::vector<const std::string>& mPaths; 
  Data mData;		            // the data retrieving object
  std::vector<cv::Mat> mOriginals;  // vector with the original decorations
  std::vector<Pattern> mPatterns; // scaled patterns  
  void encode(int); // encode entries to an array of normalized decorations
 public:
  /// get the next line to display/knit, a cv::Mat with an one pixel height
  cv::Mat nextLine();
  /// constructor
  Decoration();
  Decoration(const Decoration&) =delete; 
  Decoration& operator=(const Decoration&) =delete;
  ~Decoration() =default;
};

#endif
