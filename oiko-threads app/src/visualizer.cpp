/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#include "visualizer.h"

// ============================= Constructors ===========================

Visualizer::Visualizer(const unsigned width,
		       const unsigned height) :
  mWidth {width},
  mHeight {height},
  mLineHeight {mWidth/settings::width},
  mDisplay {static_cast<int>(mHeight), static_cast<int>(mWidth),
      CV_8UC1, cv::Scalar(0)}, 
  stillCounter {1} {
    cv::namedWindow(settings::guiWindow);
}

// ============================= Dtor ============================== 
Visualizer::~Visualizer() {
  cv::destroyAllWindows();
}

// ============================= addLine ============================== 
void Visualizer::addLine(cv::Mat mat) { 
  helper::log("updating knitting emulation"); 
  cv::resize(mat,mat,cv::Size(mWidth, mLineHeight)); // scale animation
  // move up and add line
  cv::Mat src { mDisplay
      (cv::Rect(0,mLineHeight,mWidth,mHeight - mLineHeight)) };
  cv::Mat dest { mDisplay
      (cv::Rect(0,0,mWidth,mHeight - mLineHeight)) };
  src.copyTo(dest);
  dest = mDisplay
    (cv::Rect(0,mHeight-mLineHeight,mWidth,mLineHeight));
  mat.copyTo(dest);
  cv::imshow(settings::guiWindow, mDisplay); 
}

// ============================== makeStill ==============================
cv::Mat Visualizer::makeStill(Decoration& decoration, unsigned lines,
			      unsigned targetWidth) {
  cv::Mat mat {static_cast<int>(lines), static_cast<int>(mWidth),
      CV_8UC3, cv::Scalar(255,0,0)};
  for (int i=0; i<=lines; ++i) {
    cv::Mat line {decoration.nextLine()};
    for (int j = 0; j < line.cols; j++) {
      mat.at<cv::Vec3b>(i, j)[2] = line.at<uchar>(0,j);
    }
  }
  double f{static_cast<double>(targetWidth)/static_cast<double>(mat.cols)};
  unsigned height {static_cast<unsigned>(mat.rows * f)};
  cv::resize(mat,mat,cv::Size(targetWidth,height));
  return mat;
}

// ============================= showStill ============================== 
void Visualizer::showStill(Decoration& decoration, unsigned lines,
			   unsigned targetWidth) {
  cv::Mat mat {makeStill(decoration, lines, targetWidth)};
  cv::imshow(settings::guiWindow, mat);
  cv::waitKey(0);  // wait for key
}


// ============================= exportStill ===========================
void Visualizer::exportStill(Decoration &decoration, unsigned lines,
			     unsigned targetWidth) {
  cv::Mat mat {makeStill(decoration, lines, targetWidth)};
  std::ostringstream path {};
  path << "stills/" << getCurrentDate() << "_" << stillCounter << ".tiff";
  cv::imwrite(path.str(), mat);
}

// ============================= getCurrentDate ========================
std::string Visualizer::getCurrentDate() const {
  time_t t;
  time(&t);
  std::string ts {boost::lexical_cast<std::string>(t)};
  return ts;
}
