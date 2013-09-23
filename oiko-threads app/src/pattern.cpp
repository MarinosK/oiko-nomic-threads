
#include "pattern.h"

// ============================= constructor ============================ 
Pattern::Pattern() : 
  mOutput(1,settings::width,CV_8UC1),   // output Mat
  mRowIndex(0), // mRowIndex
  mMaxHeight(1),
  mChangeIndex(1),
  mOriginals(),
  mPatterns(),
  mPaths({settings::pattern0,settings::pattern1,settings::pattern2,settings::pattern3,settings::pattern4,settings::pattern5,settings::pattern6,settings::pattern7,settings::pattern8,settings::pattern9}),
  mData(), 
  mEntry(),
  mEntryFlag(false) // mMEntryFlag
{
  mEntry.date = 0;
  mEntry.amount = 0;
}

// ============================= setUp ============================== 
void Pattern::setUp() {
  // update mPaths vector with the right mPaths (read from settings.h)
  // mPaths.push_back(settings::pattern0);
  // mPaths.push_back(settings::pattern1);
  // mPaths.push_back(settings::pattern2);
  // mPaths.push_back(settings::pattern3);
  // mPaths.push_back(settings::pattern4);
  // mPaths.push_back(settings::pattern5);
  // mPaths.push_back(settings::pattern6);
  // mPaths.push_back(settings::pattern7);
  // mPaths.push_back(settings::pattern8);
  // mPaths.push_back(settings::pattern9);
  // read images from hard disc and store them to mOriginals' vector

  for (std::vector<std::string>::iterator it = mPaths.begin() ; it != mPaths.end(); ++it) {
    cv::Mat image,binaryImage;
    image = cv::imread(*it,0);
    if (!image.data)  // check if loaded
      std::cout << "Error: pattern image " << *it << " could not be opened" << std::endl; 
    // apply threashold to make images binary
    cv::threshold(image, binaryImage, 100, 255, cv::THRESH_BINARY);
    mOriginals.push_back(binaryImage);
  }

  // for (int i=0; i<=9; i++) {
  //   cv::Mat image,binaryImage;
  //   image = cv::imread(mPaths[i],0);
  //   if (!image.data) { // check if loaded
  //     std::cout << "Error: pattern image " << mPaths[i] << " could not be opened" << std::endl; }
  //   // apply threashold to make images binary
  //   cv::threshold(image, binaryImage, 100, 255, cv::THRESH_BINARY);
  //   mOriginals.push_back( binaryImage);
  // }

  // setUp mData retreiving
  mData.setUp();
  
  // initialize random seed
  std::srand( (unsigned) std::time(NULL) ); 
}

// ============================= nextLine ============================== 
cv::Mat Pattern::nextLine() {
  if (mPatterns.empty()) {   // the first time
    
    int nextValue = nextEntry();
    mPatterns = encode(nextValue);
      
    // read one line from all patterns and copy it to mOutput
    int widthOffset = 0;

    for (std::vector<cv::Mat>::iterator it = mPatterns.begin() ; 
	 it != mPatterns.end(); ++it) {
      int cols = it->cols;
      for (int i = 0; i < cols; i++) {
	mOutput.at<uchar>(0, widthOffset + i) = it->at<uchar>(mRowIndex,i);
      }
      widthOffset += cols;
    }

    mRowIndex += 1;
    
  } else if (mRowIndex <= mChangeIndex) { 

    // read one line from all patterns and copy it to mOutput
    int widthOffset = 0;
    for (std::vector<cv::Mat>::iterator it = mPatterns.begin() ; 
	 it != mPatterns.end(); ++it) {
      int cols = it->cols;
      for (int i = 0; i < cols; i++) {
	mOutput.at<uchar>(0, widthOffset + i) = it->at<uchar>(mRowIndex,i);
      }
      widthOffset += cols;
    }

    mRowIndex += 1;

  } else { 
   
    // reset rowIndex 
    mRowIndex = 0;

    // set minimum/maximum heights befor they are reset by encode()
    unsigned int minHeight = mChangeIndex;
    unsigned int maxHeight = mMaxHeight;
    
    // read and encode next entry
    int nextValue = nextEntry();
    std::vector<cv::Mat> nextPatterns = encode(nextValue); // next set of patterns

    // set widthOffset for various calculations
    int widthOffset = 0;

    // put all non-printed parts of mPatterns into one cv::Mat
    unsigned int height = maxHeight - minHeight;
    cv::Mat oldPattern(height, settings::width, CV_8UC1, cv::Scalar(0));
    for (std::vector<cv::Mat>::iterator it = mPatterns.begin() ; 
  	 it != mPatterns.end(); ++it) {
      if (it->rows > minHeight) {
  	cv::Mat roiNew, roiOld;
  	unsigned int wi, he;
  	wi = it->cols;
  	he = (it->rows) - minHeight;
  	roiNew = oldPattern(cv::Rect(widthOffset,0,wi,he));
  	roiOld = (*it)(cv::Rect(0,minHeight,wi,he));
  	roiOld.copyTo(roiNew);
  	widthOffset += wi;
      } else {
  	unsigned int wi = it->cols;
  	widthOffset += wi;
      }
    }

    // test oldPattern
    // cv::namedWindow( "Test");
    // cv::Mat mat = oldPattern;
    // cv::resize(mat,mat,cv::Size(0,0),3,3);
    // cv::imshow( "Test", oldPattern);
    // cv::waitKey(0);  

    // clean mPatterns;
    mPatterns.clear();
    
    // merge new and old patterns and populate mPatterns
    widthOffset = 0;
    for (std::vector<cv::Mat>::iterator it = nextPatterns.begin(); 
    	 it != nextPatterns.end(); ++it) {
      unsigned int patHeight;
      if (it->rows <= height) {patHeight = it->rows;} else {patHeight = height;}
      cv::Mat dst, src, result;	// define rois
      src = oldPattern(cv::Rect(widthOffset,0,it->cols, patHeight));
      dst = (*it)(cv::Rect(0,0,it->cols,patHeight));
      // add
      cv::add(dst,src,dst);  
      mPatterns.push_back(*it);
      widthOffset += it->cols;
    }

    // calculate next line
    widthOffset = 0;
    for (std::vector<cv::Mat>::iterator it = mPatterns.begin() ; 
    	 it != mPatterns.end(); ++it) {
      int cols = it->cols;
      for (int i = 0; i < cols; i++) {
    	mOutput.at<uchar>(0, widthOffset + i) = it->at<uchar>(mRowIndex,i);
      }
      widthOffset += cols;
    }

    mRowIndex += 1;
  }

  // INVERT & THRESHOLD
  cv::threshold( mOutput, mOutput, 128, 255, cv::THRESH_BINARY_INV);
  
  // test output
  // DEBUG_PRINT(mOutput.cols);
  // DEBUG_PRINT(mOutput.rows);

  return mOutput;
}

// ============================= nextEntry ============================== 
int Pattern::nextEntry() {
  int result;
  if (!mEntryFlag) {
    mEntry = mData.nextEntry();
    result = mEntry.date;
    mEntryFlag = true;
  } else {
    result = mEntry.amount;
    mEntryFlag = false;
  }
  return result;
}

// ============================= encode ============================== 
std::vector<cv::Mat> Pattern::encode(int number) {
  // count digits and call distribute()
  int number_of_digits = (int)log10(number) + 1;
  std::vector<unsigned int> widths;
  widths = distribute(number_of_digits);

  // this vector will hold all heights so as to calculate the mChangeIndex and the mMaxHeight
  std::vector<unsigned int> heights;

  // read each digit and fill vector with *inverted* mOriginals according to entry
  std::vector<cv::Mat> result;
  std::string str = boost::lexical_cast<std::string>(number); // convert to string
  for( int i = 0; i < number_of_digits; i++ ) {
    int index =  boost::lexical_cast<int>(str[i]);
    cv::Mat pat = mOriginals[index];
    // scale 
    unsigned int x,y;
    x = widths[i];
    double f = static_cast<double>(x) / static_cast<double>(pat.cols);
    y = static_cast<unsigned int>(pat.rows * f);
    cv::Size size(x,y);
    cv::resize(pat, pat, size);
    // invert
    cv::threshold( pat, pat, 128, 255, cv::THRESH_BINARY_INV); 
    // push_back
    result.push_back(pat);
    // push_back height
    heights.push_back(pat.rows);
  }

  // calculate mChangeIndex (minHeight) and mMaxHeight
  mChangeIndex = *std::min_element(heights.begin(), heights.end());
  mMaxHeight = *std::max_element(heights.begin(), heights.end());

  return result;
}

// ============================= distribute ============================== 
std::vector<unsigned int> Pattern::distribute(int parts) {
  int sum = settings::width;
  std::vector<unsigned int> result;
  for (int i = parts; i>0; i--) {
    if (i != 1) {
      int a, b;
      a = sum / i;
      b = random( (int) (a * 0.70), (int) (a * 1.30));
      sum -= b;
      result.push_back(b);
    } else {
      result.push_back(sum);
    }
  }
  std::random_shuffle ( result.begin(), result.end() );
  return result;
}

int Pattern::random(int min, int max) {
  int result = (int) ( (max - min) * std::rand() / (float) RAND_MAX + min); 
  return result;
}
