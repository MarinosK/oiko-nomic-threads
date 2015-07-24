
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <exception>
#include <mar_utils.h>
#include <opencv2/opencv.hpp>
#include "data.h"
#include "helper.h"
#include "controller.h"

#ifdef DUAL_MODE
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"
#endif

class DataNextDigit: public testing::Test {
public:
  Data data{settings::dataFile};
};

TEST(HelperMyThrow, CorrectlyThrowExcption) {
  try { helper::myThrow<std::runtime_error>("what the fuck!!");}
  catch (const std::exception& e) {
    ASSERT_STREQ(e.what(), "what the fuck!!");
  }
}

// #ifdef DUAL_MODE
// TEST(HelperLog, CorrectlySendLogOverOSC) {
//   helper::log("test");
// }
// #endif

// TEST(HelperMyThrowOSC, CorrectlyThrowOverOSC) {

// }

TEST_F(DataNextDigit, CorrectlyReturningDigitsFromTheDataFiles) {
  std::vector<unsigned int> testCase{20131004,1241166,20131003,990520,
      20131002,805562,20131001,889925,20130930,885964,20130927,10809347,
      20130926,1864386,20130925,2463751,20130924,904873,20130923,1815370,
      20130920,102184479,20130919,454738,20130918,23545,20130917,169805,
      20130916,353,20130913,436473,20130912,86012,20130911,3378666}; 
  for (auto testElement : testCase) {
    auto datum = data.nextDigit();
    ASSERT_THAT(datum, testing::Eq(testElement));
  }
}

TEST(MarIrregularDistribution, CorrectyDistributingParts) {
  auto a = mar::irregular_distribution<int>(100,7,0.60);
  ASSERT_THAT(std::accumulate(a.begin(),a.end(),0),100);
}

TEST(MarRandom, CorrectlyReturnRandomNumbers) {
  int a {mar::random<>(10,100)}; 
  double b {mar::random<double>(10.0,100.0)}; 
  unsigned int c {mar::random<unsigned int>(50)};
  ASSERT_LE(a, 100); ASSERT_GE(a, 10);
  ASSERT_LE(b, 100); ASSERT_GE(b, 10);
  ASSERT_LE(c, 50); 
}

// class ControllerTest: public testing::Test {
// public:
//   Controller ctrl{};
// }

TEST(ControllerTest, CorrectOsOperator) {
   cv::Mat mat{
     1,static_cast<int>(settings::knitWidth),CV_8UC1,cv::Scalar(0) };
   for (int pix = 50; pix < mat.cols; ++pix) mat.at<uchar>(0, pix) = 250;
   std::ostringstream str{};
   str << mat;
   std::ostringstream test{};
   std::string a (50,'0');
   std::string b (mat.cols-50,'1');
   test << a << b;
   ASSERT_STREQ(test.str().c_str(), str.str().c_str());
}

int main(int argc, char** argv) {
  testing::InitGoogleMock(&argc, argv);
  std::cout.rdbuf(nullptr); // supress cout
  return RUN_ALL_TESTS();
}
