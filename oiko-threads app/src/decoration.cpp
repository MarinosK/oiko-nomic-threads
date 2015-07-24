
#include "decoration.h"

// ============================= constructor ============================ 
Decoration::Decoration() :
  mPaths {settings::pathsToOriginalMottifs},
  mData {settings::dataFile}, 
  mOriginals {},
  mPatterns {} {
    for (auto& element : mPaths) { // load all images  
      cv::Mat image {};
      image = cv::imread(element,0);
      if (!image.data) {
	std::ostringstream error{};
	error << "decoration " << element << " could not be loaded";
	helper::myThrow<std::runtime_error>(error.str());
      }
      cv::threshold(image, image, 250, 255, cv::THRESH_BINARY_INV); 
      mOriginals.emplace_back(image);
    }
}

// ============================= nextLine ============================== 
cv::Mat Decoration::nextLine() {
  if (mPatterns.empty()) encode(mData.nextDigit()); // if empty, fill

  auto donePred = [] (const Segment& seg) { return seg.done();}; // c++14 

  // when some encoded "number" is partially done, add another
  auto latest = mPatterns.back();
  if (std::any_of(latest.begin(), latest.end(), donePred))
    encode(mData.nextDigit());
  
  // clean up everything
  for (auto& vec : mPatterns) 
    vec.erase(std::remove_if(vec.begin(),vec.end(),donePred), vec.end());
  mPatterns.erase(std::remove_if(mPatterns.begin(),mPatterns.end(),
				 [](const Pattern vec){
				   return vec.empty(); }),
		  mPatterns.end());
  
  // calculate new line
  cv::Mat output{
    1,static_cast<int>(settings::width),CV_8UC1,cv::Scalar(0) }; 
  for (auto& pat : mPatterns) {
    for (auto& seg : pat) {
      cv::Mat lineSegment = seg.getNextLineSegment();
      cv::Mat dest = output(cv::Rect(seg.getPositionIndex(),
				     0,seg.getWidth(),1));
      cv::add(lineSegment,dest,dest);
    }
  }

  return output;
}

// ============================= encode ============================== 
void Decoration::encode(int number) { // fills mPatterns with new mats    

  auto number_as_string = boost::lexical_cast<std::string>(number);
  int number_of_digits {static_cast<int>(number_as_string.length())};
  auto widthsVec = mar::irregular_distribution // vector of desired widths
    <unsigned>(settings::width, number_of_digits, 0.40); 
  unsigned positionIndex {0};

  Pattern groupOfPatterns {};
  for (auto digit_as_char : number_as_string) {
    // select motif from the originals
    int index {boost::lexical_cast<int>(digit_as_char)};
    cv::Mat motif {mOriginals[index]};
    // scale it
    unsigned width {widthsVec.back()}; 
    double f {static_cast<double>(width)/static_cast<double>(motif.cols)};
    unsigned height {static_cast<unsigned>(motif.rows * f)};
    cv::resize(motif, motif, cv::Size(width,height));  
    // update variables
    Segment seg(motif,positionIndex);
    positionIndex += width;
    groupOfPatterns.emplace_back(seg);
    widthsVec.pop_back(); // pop width used 
  }
  mPatterns.emplace_back(groupOfPatterns);
}
