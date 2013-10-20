/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#include "pattern.h"


// ============================= constructor ============================ 
Pattern::Pattern() : 
  mOutput(1,settings::width,CV_8UC1,cv::Scalar(0)),   // output Mat
  mOriginals(),
  mPatterns(),
  mPaths({settings::pattern0,settings::pattern1,settings::pattern2,settings::pattern3,settings::pattern4,settings::pattern5,settings::pattern6,settings::pattern7,settings::pattern8,settings::pattern9}),
  mData(), 
  mEntry(),
  mEntryFlag(false) // mMEntryFlag
  // patternIterator(mPatterns.begin())
{
  mEntry.date = 0;
  mEntry.amount = 0;
}

// ============================= setUp ============================== 
void Pattern::setUp() {

  for (std::vector<std::string>::iterator it = mPaths.begin() ; it != mPaths.end(); ++it) {
    cv::Mat image;
    image = cv::imread(*it,0);
    if (!image.data)  // check if loaded
      std::cout << "Error: pattern image " << *it << " could not be opened" << std::endl; 
    mOriginals.push_back(image);
  }

  // setUp mData retreiving
  mData.setUp();
  
  // initialize random seed
  std::srand( (unsigned) std::time(NULL) ); 

  // retrieve first entry and encode first block
  int nextValue = nextEntry();
  mPatterns.push_back(encode(nextValue));
}

// ============================= nextLine ============================== 
cv::Mat Pattern::nextLine() {

  mOutput = cv::Mat(1,settings::width,CV_8UC1,cv::Scalar(0));
  
   
    // if something is done from the patternIterator and on add new patterns to the existing ones
    std::vector<Segment> lastPatterns = mPatterns.back();
    if (std::any_of(lastPatterns.begin(), lastPatterns.end(), [](const Segment &seg) {return seg.done();})) {
      // retrieve next entry and encode block
      int nextValue = nextEntry();
      mPatterns.push_back(encode(nextValue));
    }
	
    // delete patterns that have ended 
    for (std::vector<std::vector<Segment> >::iterator it = mPatterns.begin(); it != mPatterns.end(); ++it) {
      it->erase(std::remove_if( it->begin(), it->end(), [](const Segment &seg){return seg.done();}),it->end());  
    }

    // draw patterns
    for (std::vector<std::vector<Segment> >::iterator itPat = mPatterns.begin(); itPat != mPatterns.end(); ++itPat) {
      for (std::vector<Segment>::iterator it = itPat->begin(); it != itPat->end(); ++it) {
	cv::Mat lineSegment = it->getNextLineSegment();
	cv::Mat dest = mOutput(cv::Rect(it->getWidthIndex(),0,it->getWidth(),1));
	cv::add(lineSegment,dest,dest); 
      }
    }
 
  // THRESHOLD
    cv::threshold( mOutput, mOutput, 250, 255, cv::THRESH_BINARY);

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
std::vector<Segment> Pattern::encode(int number) {
  // count digits and call distribute()
  int number_of_digits = (int)log10(number) + 1;
  std::vector<unsigned int> widths;
  widths = distribute(number_of_digits);

  // this vector will hold all heights so as to calculate the mChangeIndex and the mMaxHeight
  std::vector<unsigned int> heights;

  // read each digit and fill vector with *inverted* mOriginals according to entry
  std::vector<Segment> result;
  std::string str = boost::lexical_cast<std::string>(number); // convert to string
  unsigned int widthIndex = 0;
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
    cv::threshold( pat, pat, 10, 255, cv::THRESH_BINARY_INV); 
    //     cv::threshold( pat, pat, 254, 255, cv::THRESH_BINARY_INV); 
    // push_back
    Segment seg(pat,widthIndex);
    widthIndex += x;
    result.push_back(seg);
    // push_back height
    heights.push_back(pat.rows);
  }
  
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
