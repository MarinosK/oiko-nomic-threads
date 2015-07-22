#include "oikoThreadsApp.h"

// ============================= constructor =============================
OikoThreadsApp::OikoThreadsApp(unsigned int width, unsigned int height) :
  decoration {},
  visualizer {width, height},
#ifndef EMULATION_MODE
  arduino {},
  counter {0},
#endif
  nextLine {decoration.nextLine()} {
  }

// ================================ loop ================================
void OikoThreadsApp::loop() {
#ifndef EMULATION_MODE
  // send a line to the machine every 10 iterations 
  if (counter++ == 0 ) 
    if (arduino.sendMsg(nextLine)) { // if conection open, proceed
      arduino.waitForMsg();
#endif
      visualizer.addLine(nextLine);
      // REMEMBER THE TRICK WITH THE EXTRA LINES!!!
      nextLine = decoration.nextLine(); 
      cv::waitKey(settings::speed);
#ifndef EMULATION_MODE
    } else helper::log("communication with the machine interrupted");
  if (counter == 10) counter = 0;
#endif
}
