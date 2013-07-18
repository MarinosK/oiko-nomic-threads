
#include "pattern.h"

void Pattern::setUp() {
  // update mPaths vector with the right mPaths (read from settings.h)
  mPaths.push_back(PATTERN0);
  mPaths.push_back(PATTERN1);
  mPaths.push_back(PATTERN2);
  mPaths.push_back(PATTERN3);
  mPaths.push_back(PATTERN4);
  mPaths.push_back(PATTERN5);
  mPaths.push_back(PATTERN6);
  mPaths.push_back(PATTERN7);
  mPaths.push_back(PATTERN8);
  mPaths.push_back(PATTERN9);
  // read images from hard disc and store them to mOriginals' vector
  for (int i=0; i<=9; i++) {
    cv::Mat image,binaryImage;
    image = cv::imread(mPaths[i],0);
    if (!image.data) { // check if loaded
      std::cout << "Error: pattern image " << mPaths[i] << " could not be opened" << std::endl; }
    // apply threashold to make images binary
    cv::threshold(image, binaryImage, 100, 255, cv::THRESH_BINARY);
    mOriginals.push_back( binaryImage);
  }
  // setUp mData retreiving
  mData.setUp();
  // create the output Mat
  mOutput = cv::Mat(1,WIDTH,CV_8UC1);
  // initiallize mRowIndex
  mRowIndex = 0;
  // initiallize mMEntryFlag
  mEntryFlag = false;
  // initialize random seed
  std::srand( (unsigned) std::time(NULL) ); 
}

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
      widthOffset += it->cols;
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
      widthOffset += it->cols;
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
    cv::Mat oldPattern(height, WIDTH,CV_8UC1, cv::Scalar(255));
    
    for (std::vector<cv::Mat>::iterator it = mPatterns.begin() ; 
	 it != mPatterns.end(); ++it) {
      if (it->rows > minHeight) {
      // 	unsigned int cols = it->cols;
      // 	unsigned int rows = it->rows - minHeight;
      // 	for (int i = 0; i < rows; i++) {
      // 	  for (int j = 0; j < cols; j++) {
      // 	    oldPattern.at<uchar>(i, widthOffset + j) = it->at<uchar>(i+minHeight,j);
      // 	  }
      // 	} 
      cv::Mat roiNew, roiOld;
      int wi, he;
      wi = it->cols;
      he = (it->rows) - minHeight;
      roiNew = oldPattern(cv::Rect(widthOffset,0,wi,he));
      roiOld = (*it)(cv::Rect(0,minHeight,wi,he));
      roiOld.copyTo(roiNew);
      widthOffset += it->cols;
      }
    }

    // test oldPattern
    // cv::namedWindow( "Test");
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
      // maybe there is a fastest way to calculate this ??
      cv::threshold( src, src, 128, 255, cv::THRESH_BINARY_INV); // invert 
      cv::threshold( dst, dst, 128, 255, cv::THRESH_BINARY_INV); // invert 
      cv::add(dst,src,dst);  
      cv::threshold( dst, dst, 128, 255, cv::THRESH_BINARY_INV); // invert 
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
      widthOffset += it->cols;
    }
    mRowIndex += 1;

    // mPatterns = nextPatterns;

  }
  
  return mOutput;
}

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

std::vector<cv::Mat> Pattern::encode(int number) {
  // count digits and call distribute()
  int number_of_digits = (int)log10(number) + 1;
  std::vector<unsigned int> widths;
  widths = distribute(number_of_digits);

  // read each digit and fill vector with mOriginals according to entry
  std::vector<cv::Mat> draftPattern;
  std::string str = boost::lexical_cast<std::string>(number); // convert to string
  for( int i = 0; i < number_of_digits; i++ ) {
    int index =  boost::lexical_cast<int>(str[i]);
    cv::Mat pat = mOriginals[index];
    draftPattern.push_back(pat);
  }
  
  // this vector will hold all heights so as to calculate the mChangeIndex and the mMaxHeight
  std::vector<unsigned int> heights;

  // scale images
  std::vector<cv::Mat> result;
  for( int i = 0; i < number_of_digits; i++ ) {
    cv::Mat src;
    draftPattern[i].copyTo(src);
    unsigned int x,y;
    x = widths[i];
    double f = (double) x / (double) src.cols;
    y = (unsigned int) (src.rows * f);
    cv::Size size(x,y);
    cv::resize(src, src, size);
    result.push_back(src);
    // push_back height
    heights.push_back(src.rows);
  }  

  // calculate mChangeIndex (minHeight) and mMaxHeight
  mChangeIndex = *std::min_element(heights.begin(), heights.end());
  mMaxHeight = *std::max_element(heights.begin(), heights.end());

  return result;
}

std::vector<unsigned int> Pattern::distribute(int parts) {
  int sum = WIDTH;
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
