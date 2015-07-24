#include "oikoThreadsApp.h"

// ============================= constructor =============================
OikoThreadsApp::OikoThreadsApp(unsigned int width, unsigned int height) :
  visualizer {width, height},
#ifndef EMULATION_MODE
  arduino {},
  counter {0},
#endif
  decoration {} {
  }

// ================================ loop ================================
void OikoThreadsApp::loop() {
  cv::Mat nextLine{decoration.nextLine()};
  visualizer.addLine(nextLine);
#ifndef EMULATION_MODE
  cv::Mat knitLine{nextLine};
  cv::resize(knitLine,knitLine,cv::Size(settings::knitWidth,1));
  if (counter++ == 0 ) 
    if (arduino.sendMsg(knitLine)) { // if conection open, proceed
      arduino.waitForMsg();
    } else helper::log("communication with the machine interrupted");
  if (counter >= 10) counter = 0;
#endif
  cv::waitKey(settings::speed);
}
