
#include "controller.h"

// =============================== static ===============================
const std::string Controller::arduinoID {settings::hardwarePath};

// ============================== ctor/dtor ==============================
Controller::Controller() :
  mFd {arduino_lib::serialport_init(arduinoID.c_str(), mBaudRate)} {
    if (mFd == -1) helper::myThrow<std::runtime_error>
		     ("failed to communicate over serial");
    else helper::log("serial communication has been initialised");
    // arduino_lib::serialport_flush(mFd);     // flush serial port
}

Controller::~Controller() {
  arduino_lib::serialport_close(mFd);
}

// ============================= operator<< =============================
std::ostringstream& operator<< (std::ostringstream& os, const cv::Mat& mat) {
  for (int i = 0; i< mat.cols; ++i) {
    uchar bit {mat.at<uchar>(0, i)};
    if (bit==0) os << 0; else os << 1;
  }
  return os;
}

// =============================== sendMsg ===============================
bool Controller::sendMsg(const cv::Mat& mat) {
  helper::log
    ("attempting to send next line of pixels to knitting machine..");
  if (mFd == -1) {
    helper::log
      ("serial communication has been interrupted - pixels were not sent");
    return false;
  } else {
    std::ostringstream data{};
    data << mat;
#ifdef DEBUG
    //DEBUG_PRINT(data.str().c_str());
    std::cout << "sending the folowing stitch-pattern to the machine:"
	      << std::endl;
    auto test = data.str();
    for (int i = 0; i< test.size(); ++i) {
      std::cout << test[i];
      if ((i%8)==7) std::cout << " ";
      if ((i%16)==15) std::cout << std::endl;
    }
#endif 
    if (!arduino_lib::serialport_write(mFd, data.str().c_str()))
      return true;
    else {
      helper::log("error sending the pixels to the machine");
      return false;
    }
  }
}

bool Controller::sendMsg(const std::string& data) {
  if (mFd == -1) {
    helper::log
      ("serial communication has been interrupted - pixels were not sent");
    return false;
  } else {
    if (!arduino_lib::serialport_write(mFd, data.c_str()))
      return true;
    else {
      helper::log("error sending the pixels to the machine");
      return false;
    }
  }
}


// ============================= waitForMsg =============================
bool Controller::waitForMsg() {
  helper::log("waiting for machine to knit line");
  if (mFd == -1) {
    helper::log("serial communication has been interrupted: the machine never responded whether line has been sucessfully knitted or not");
    return false;
  } else {
    int bufferSize {7};
    char endOfLine {'\n'};
    char buf[bufferSize]; 
    memset(buf,0,bufferSize); 
    arduino_lib::serialport_read_until(mFd, buf, endOfLine, bufferSize,
				       100000);
    std::string msg{buf};  
    if (msg == "done!\n")
      helper::log("machine's response was positive: line has been knitted succesfully!");
    else 
      helper::log("the knitting machine did respond, but the response was incomprehensible or the request timed out: it is not known whether line has been sucessfully knitted or not");
    return true;
  }
}
