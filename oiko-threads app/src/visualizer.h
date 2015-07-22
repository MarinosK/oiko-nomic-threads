/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/
#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <string>
#include <sstream>
#include <ctime>
#include <boost/lexical_cast.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "helper.h"
#include "decoration.h"

/// Visualizer is responsible for the GUI and for processing all visualization requests (including the live demo and exporting stills)
class Visualizer {
private:
  const unsigned mWidth, mHeight;  
  const unsigned mLineHeight;  // factor to proportionally scale the animation
  cv::Mat mDisplay;	       
  std::string getCurrentDate() const;  // used to name Stills
  cv::Mat makeStill(Decoration&, unsigned, unsigned);
  short stillCounter;
 public:
  /// constructor 
  Visualizer(const unsigned width, const unsigned height); // ctor
  /// default constructor
  Visualizer() : Visualizer(settings::width, settings::height) {};
  /// destructor
  ~Visualizer();
  Visualizer(const Visualizer&) =delete;
  Visualizer(Visualizer&&) =delete;
  Visualizer& operator=(const Visualizer&) =delete; 
  Visualizer& operator=(Visualizer&&) =delete; 

  /// add a new line to the GUI Animation
  void addLine(cv::Mat mat);
  /// make and show a still image of n lines  
  void showStill(Decoration &decoration, unsigned lines, unsigned width);
  /// make and export a still image of n lines
  void exportStill(Decoration &decoration, unsigned lines,unsigned width);
};

#endif
