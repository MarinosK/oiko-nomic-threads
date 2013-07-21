/*
  part of Oikonomic Threads project
  coded by Marinos Koutsomichalis (c) 2013, Heraklion
*/

#include "visualizer.h"

// ============================= Constructor ============================== 
Visualizer::Visualizer() :
  stillsIndex(0)
{
  cv::namedWindow( "Oiko-nomic Threads: Display window");
}

// ============================= animate ============================== 
void Visualizer::animate(Pattern &pattern) { // not yet implemented !
  unsigned int height = WIDTH * 3;
  cv::Mat mat(height, WIDTH, CV_8UC3, cv::Scalar(0,0,255));
  unsigned int lineIndex = 0;
  
  // first screen
  for (int i=0; i<=height; i++) {
    cv::Mat line = pattern.nextLine();
    for (int j = 0; j < line.cols; j++) {
      mat.at<cv::Vec3b>(i, j)[1] = line.at<uchar>(0,j);
    }

    while(true) {
      
      // delete first line and move everything one line up

      // add last line
      for (int j = 0; j < WIDTH; j++) {
	cv::Mat line = pattern.nextLine();
	mat.at<cv::Vec3b>(height,j)[1] = line.at<uchar>(0,j);
      }
      cv::resize(mat,mat,cv::Size(0,0),3,3);
      cv::imshow( "Oiko-nomic Threads: Display window", mat );
      // wait time somehow !!!
      
    }
  }
}

// ============================= still ============================== 
void Visualizer::still(Pattern &pattern, int lines) {
  cv::Mat mat(lines, WIDTH, CV_8UC3, cv::Scalar(255,0,0));
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
  cv::Mat mat(lines, WIDTH, CV_8UC3, cv::Scalar(0,0,255));
  for (int i=0; i<=lines; i++) {
    cv::Mat line = pattern.nextLine();
    for (int j = 0; j < line.cols; j++) {
      mat.at<cv::Vec3b>(i, j)[1] = line.at<uchar>(0,j);
    }
  }
  
  // save
  std::string date = getCurrentDate();
  std::string index = boost::lexical_cast<std::string>(stillsIndex);
  std::string path = "stills/still " ;
  path.append(date);
  path.append(index);
  path.append(".tiff");
  cv::imwrite(path, mat);

  stillsIndex++;
}

// ============================= clean ============================== 
void Visualizer::clean() {
  cv::destroyAllWindows();
}

// ============================= test ============================== 
void Visualizer::test(cv::Mat image) {
  cv::namedWindow( "Test");
  cv::imshow( "Test", image);
  cv::waitKey(0);  
}

// ============================= getCurrentDate ============================== 
std::string Visualizer::getCurrentDate() {
  time_t t;
  time(&t);
  std::string ts = boost::lexical_cast<std::string>(t);
  return ts;
}
