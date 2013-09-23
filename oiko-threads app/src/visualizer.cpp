/*
  part of Oikonomic Threads project
  coded by Marinos Koutsomichalis (c) 2013, Heraklion
*/

#include "visualizer.h"

// ============================= Constructors ===========================
Visualizer::Visualizer() :
  mWidth( settings::width * 8 ),
  mHeight(settings::width * 5 ),
  mLineHeight(mWidth/settings::width),
  mStillsIndex(0),
  mImage(mHeight, mWidth, CV_8UC1, cv::Scalar(0))
{
  cv::namedWindow( "Oiko-nomic Threads: Knitting emulation.");
}

Visualizer::Visualizer(const unsigned int mWidth_, const unsigned int mHeight_) :
  mWidth(mWidth_),
  mHeight(mHeight_),
  mLineHeight(mWidth/settings::width),
  mStillsIndex(0),
  mImage(mHeight, mWidth, CV_8UC1, cv::Scalar(0))
{
  cv::namedWindow( "Oiko-nomic Threads: Knitting emulation.");
}

// ============================= Dtor ============================== 
Visualizer::~Visualizer() {
  cv::destroyAllWindows();
}

// ============================= animate ============================== 
void Visualizer::animate(cv::Mat mat) { 

  std::cout << "Updating knitting emulation." << std::endl; // post info

  cv::resize(mat,mat,cv::Size(mWidth, mLineHeight)); // reshize input

  // move the whole image upwards
  { // block for optimization
    cv::Mat source = mImage(cv::Rect(0,mLineHeight,mWidth,mHeight - mLineHeight));
    cv::Mat destination = mImage(cv::Rect(0,0,mWidth,mHeight - mLineHeight));
    source.copyTo(destination);
  }

  // set new line
 { // block for optimization
  cv::Mat dstRoi = mImage(cv::Rect(0,mHeight-mLineHeight,mWidth,mLineHeight));
  mat.copyTo(dstRoi);
 }
  
  // update display
  cv::imshow( "Oiko-nomic Threads: Knitting emulation.", mImage );
}

// ============================= still ============================== 
void Visualizer::still(Pattern &pattern, int lines) {
  cv::Mat mat(lines, settings::width, CV_8UC3, cv::Scalar(255,0,0));

  for (int i=0; i<=lines; i++) {
    cv::Mat line = pattern.nextLine();
    for (int j = 0; j < line.cols; j++) {
      mat.at<cv::Vec3b>(i, j)[2] = line.at<uchar>(0,j);
    }
  }
  
  // resize
  cv::resize(mat,mat,cv::Size(0,0),3,3);
  
  // display and wait for key
  cv::imshow( "Oiko-nomic Threads: Display window", mat );
  cv::waitKey(0);  
}

// ============================= exportStill ============================== 
void Visualizer::exportStill(Pattern &pattern, int lines) {
  cv::Mat mat(lines, settings::width, CV_8UC3, cv::Scalar(0,0,255));
  for (int i=0; i<=lines; i++) {
    cv::Mat line = pattern.nextLine();
    for (int j = 0; j < line.cols; j++) {
      mat.at<cv::Vec3b>(i, j)[1] = line.at<uchar>(0,j);
    }
  }
  
  // save
  std::string date = getCurrentDate();
  std::string index = boost::lexical_cast<std::string>(mStillsIndex);
  std::string path = "stills/still " ;
  path.append(date);
  path.append(index);
  path.append(".tiff");
  cv::imwrite(path, mat);

  mStillsIndex++;
}

// ============================= test ============================== 
void Visualizer::test(cv::Mat image) {
  cv::namedWindow( "Test");
  cv::imshow( "Test", image);
  cv::waitKey(0);  
}

// ============================= getCurrentDate ========================
std::string Visualizer::getCurrentDate() {
  time_t t;
  time(&t);
  std::string ts = boost::lexical_cast<std::string>(t);
  return ts;
}
